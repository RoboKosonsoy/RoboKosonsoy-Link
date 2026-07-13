#include "Parser.h"
#include "../core/CRC16.h"
#include "../core/Config.h"

namespace RKL
{

Result Parser::parse(const uint8_t* buffer,
                     uint16_t size,
                     Packet& packet)
{
    if (buffer == nullptr)
        return Result::INVALID_PARAMETER;

    if (size < PACKET_HEADER_SIZE + CRC_SIZE)
        return Result::INVALID_PACKET;

    if (buffer[0] != START_BYTE)
        return Result::INVALID_PACKET;

    if (buffer[1] != PROTOCOL_VERSION)
        return Result::INVALID_PACKET;

    const uint8_t payloadLength = buffer[6];
    if (payloadLength > MAX_PAYLOAD_SIZE)
        return Result::BUFFER_OVERFLOW;

    const uint16_t expectedSize = PACKET_HEADER_SIZE + payloadLength + CRC_SIZE;
    if (size != expectedSize)
        return Result::INVALID_PACKET;

    const uint16_t receivedCrc =
        (static_cast<uint16_t>(buffer[PACKET_HEADER_SIZE + payloadLength]) << 8) |
        buffer[PACKET_HEADER_SIZE + payloadLength + 1];

    uint8_t crcBuffer[MAX_PACKET_SIZE];
    crcBuffer[0] = buffer[1];
    crcBuffer[1] = buffer[2];
    crcBuffer[2] = buffer[3];
    crcBuffer[3] = buffer[4];
    crcBuffer[4] = buffer[5];
    crcBuffer[5] = buffer[6];
    if (payloadLength > 0)
        memcpy(crcBuffer + 6, buffer + PACKET_HEADER_SIZE, payloadLength);

    if (!CRC16::verify(crcBuffer, 6 + payloadLength, receivedCrc))
        return Result::CRC_ERROR;

    packet.clear();
    packet.start = buffer[0];
    packet.version = buffer[1];
    packet.type = static_cast<PacketType>(buffer[2]);
    packet.flags = buffer[3];
    packet.counter = (static_cast<uint16_t>(buffer[4]) << 8) | buffer[5];
    packet.length = payloadLength;

    if (payloadLength > 0)
        memcpy(packet.payload, buffer + PACKET_HEADER_SIZE, payloadLength);

    packet.crc = receivedCrc;

#if RKL_DEBUG
    RKL_LOGLN("");
    RKL_LOGLN("========== RX FRAME ==========");
    RKL_LOG("VER   : "); RKL_LOGLN(packet.version);
    RKL_LOG("TYPE  : "); RKL_LOGLN((uint8_t)packet.type);
    RKL_LOG("FLAGS : "); RKL_LOGLN(packet.flags);
    RKL_LOG("COUNTER: "); RKL_LOGLN(packet.counter);
    RKL_LOG("LEN   : "); RKL_LOGLN(packet.length);
    RKL_LOG("CRC   : "); RKL_LOGLN(packet.crc, HEX);
    RKL_LOG("SIZE  : "); RKL_LOGLN(size);
    RKL_LOG("HEX   : "); RKL_DebugHex(buffer, size);
    RKL_LOGLN("==============================");
    RKL_LOGLN("");
#endif

    return Result::OK;
}

} // namespace RKL