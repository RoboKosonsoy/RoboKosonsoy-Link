#include "Link.h"

#include "Parser.h"
#include "Serializer.h"

namespace RKL
{

Link::Link(Radio& radio)
    : _radio(radio),
      _ack(),
      _retry(),
      _nextSequence(0)
{
}

void Link::setRetryConfig(const RetryConfig& config)
{
    _retry.configure(config);
}

uint8_t Link::nextSequence()
{
    return _nextSequence++;
}

Result Link::sendPacket(Packet& packet)
{
    if (packet.type != PacketType::ACK)
        packet.id = nextSequence();

    _retry.reset();

    while (_retry.canAttempt())
    {
        _retry.recordAttempt();

        Result result = sendOnce(packet);
        if (result != Result::OK)
            return result;

        if (packet.type == PacketType::ACK)
            return Result::OK;

        result = waitForAck(packet.id, _retry.timeout());
        if (result == Result::OK)
            return Result::OK;
    }

    return Result::RETRY_EXHAUSTED;
}

Result Link::receivePacket(Packet& packet, uint16_t timeout)
{
    uint16_t received = 0;
    Result result = readFrame(received, timeout);

    if (result != Result::OK)
        return result;

    result = Parser::parse(_buffer, received, packet);
    if (result != Result::OK)
        return result;

    if (packet.type == PacketType::ACK)
        return Result::OK;

    Packet ackPacket;
    Ack::make(ackPacket, packet.id);
    sendOnce(ackPacket);

    if (_ack.isDuplicate(packet))
        return Result::DUPLICATE_PACKET;

    return Result::OK;
}

Result Link::send(Packet& packet)
{
    return sendPacket(packet);
}

Result Link::receive(Packet& packet)
{
    return receivePacket(packet, LINK_TIMEOUT);
}

Result Link::sendOnce(Packet& packet)
{
    uint16_t written = 0;
    Result result = Serializer::serialize(packet, _buffer, sizeof(_buffer), written);

    if (result != Result::OK)
        return result;

    return _radio.send(_buffer, written);
}

Result Link::waitForAck(uint8_t sequence, uint16_t timeout)
{
    const uint32_t start = millis();
    Packet incoming;

    while (millis() - start < timeout)
    {
        Result result = receivePacket(incoming, timeout);

        if (result == Result::OK && _ack.isAckFor(incoming, sequence))
            return Result::OK;

        if (result == Result::TIMEOUT)
            return Result::TIMEOUT;
    }

    return Result::TIMEOUT;
}

Result Link::readByte(uint8_t& value, uint32_t deadline)
{
    while (!_radio.available())
    {
        if (static_cast<int32_t>(millis() - deadline) >= 0)
            return Result::TIMEOUT;

        delay(1);
    }

    return _radio.receive(&value, 1) == 1 ? Result::OK : Result::NOT_READY;
}

Result Link::readFrame(uint16_t& frameSize, uint16_t timeout)
{
    frameSize = 0;
    const uint32_t deadline = millis() + timeout;
    uint8_t value = 0;

    do
    {
        Result result = readByte(value, deadline);
        if (result != Result::OK)
            return result;
    }
    while (value != START_BYTE);

    _buffer[0] = value;

    for (uint8_t i = 1; i < PACKET_HEADER_SIZE; i++)
    {
        Result result = readByte(_buffer[i], deadline);
        if (result != Result::OK)
            return result;
    }

    const uint8_t payloadLength = _buffer[3];
    if (payloadLength > MAX_PAYLOAD_SIZE)
        return Result::BUFFER_OVERFLOW;

    frameSize = PACKET_HEADER_SIZE + payloadLength + CRC_SIZE;

    for (uint16_t i = PACKET_HEADER_SIZE; i < frameSize; i++)
    {
        Result result = readByte(_buffer[i], deadline);
        if (result != Result::OK)
            return result;
    }

    return Result::OK;
}

} // namespace RKL
