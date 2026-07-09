#include <RKL.h>

class MemoryRadio : public RKL::Radio
{
public:
    MemoryRadio()
        : rxLength(0),
          rxIndex(0),
          txLength(0)
    {
    }

    RKL::Result begin() override
    {
        return RKL::Result::OK;
    }

    bool available() override
    {
        return rxIndex < rxLength;
    }

    RKL::Result send(const uint8_t* data, size_t length) override
    {
        if (length > sizeof(tx))
            return RKL::Result::BUFFER_OVERFLOW;

        memcpy(tx, data, length);
        txLength = length;

        if (length >= RKL::PACKET_HEADER_SIZE + RKL::CRC_SIZE &&
            data[1] != static_cast<uint8_t>(RKL::PacketType::ACK))
        {
            RKL::Packet ack;
            RKL::Ack::make(ack, data[2]);
            uint16_t written = 0;
            return RKL::Serializer::serialize(ack, rx, sizeof(rx), written) == RKL::Result::OK
                ? setRxLength(written)
                : RKL::Result::INVALID_PACKET;
        }

        return RKL::Result::OK;
    }

    size_t receive(uint8_t* buffer, size_t length) override
    {
        size_t count = 0;

        while (count < length && rxIndex < rxLength)
            buffer[count++] = rx[rxIndex++];

        return count;
    }

    RKL::Result waitReady(uint16_t timeout = 500) override
    {
        (void)timeout;
        return RKL::Result::OK;
    }

    RKL::Result load(const RKL::Packet& packet)
    {
        RKL::Packet copy = packet;
        uint16_t written = 0;
        RKL::Result result = RKL::Serializer::serialize(copy, rx, sizeof(rx), written);

        if (result != RKL::Result::OK)
            return result;

        return setRxLength(written);
    }

    uint16_t txLength;

private:
    RKL::Result setRxLength(uint16_t length)
    {
        rxLength = length;
        rxIndex = 0;
        return RKL::Result::OK;
    }

    uint8_t rx[RKL::MAX_PACKET_SIZE];
    uint16_t rxLength;
    uint16_t rxIndex;
    uint8_t tx[RKL::MAX_PACKET_SIZE];
};

void printResult(const char* label, RKL::Result result)
{
    Serial.print(label);
    Serial.print(": ");
    Serial.println(result == RKL::Result::OK ? "OK" : "ERROR");
}

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    Serial.println("=== RKL Packet Test ===");

    RKL::Packet packet;
    packet.type = RKL::PacketType::PING;
    packet.id = 42;

    const uint8_t payload[] = {'R', 'K', 'L'};
    printResult("setPayload", packet.setPayload(payload, sizeof(payload)));

    uint8_t buffer[RKL::MAX_PACKET_SIZE];
    uint16_t written = 0;

    RKL::Result result = RKL::Serializer::serialize(packet, buffer, sizeof(buffer), written);
    printResult("serialize", result);

    RKL::Packet parsed;
    result = RKL::Parser::parse(buffer, written, parsed);
    printResult("parse", result);

    Serial.print("Type: 0x");
    Serial.println(static_cast<uint8_t>(parsed.type), HEX);
    Serial.print("Sequence: ");
    Serial.println(parsed.id);
    Serial.print("Payload length: ");
    Serial.println(parsed.length);
    Serial.print("CRC: 0x");
    Serial.println(parsed.crc, HEX);

    MemoryRadio radio;
    RKL::Link link(radio);

    RKL::Packet outbound;
    outbound.type = RKL::PacketType::PING;
    outbound.setPayload(payload, sizeof(payload));
    printResult("link send", link.send(outbound));

    RKL::Packet inbound;
    inbound.type = RKL::PacketType::TELEMETRY;
    inbound.id = 7;
    inbound.setPayload(payload, sizeof(payload));
    printResult("load inbound", radio.load(inbound));

    RKL::Packet received;
    printResult("link receive", link.receive(received));
    Serial.print("ACK bytes sent: ");
    Serial.println(radio.txLength);
}

void loop()
{
}
