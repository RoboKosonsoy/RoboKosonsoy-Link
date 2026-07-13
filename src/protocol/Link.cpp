#include "Link.h"
#include "Parser.h"
#include "Serializer.h"

namespace RKL
{

Link::Link(Radio& radio)
    : _radio(radio),
      _ack(),
      _retry(),
      _nextCounter(0)
{
}

void Link::setRetryConfig(const RetryConfig& config)
{
    _retry.configure(config);
}

uint16_t Link::nextCounter()
{
    return _nextCounter++;
}

Result Link::sendPacket(Packet& packet)
{
    if (packet.type != PacketType::ACK)
        packet.counter = nextCounter();

    _retry.reset();

    while (_retry.canAttempt())
    {
        _retry.recordAttempt();

        Result result = sendOnce(packet);
        if (result != Result::OK)
            return result;

        if (packet.type == PacketType::ACK)
            return Result::OK;

        result = waitForAck(packet.counter, _retry.timeout());
        if (result == Result::OK)
            return Result::OK;
    }

    return Result::RETRY_EXHAUSTED;
}

Result Link::receivePacket(Packet& packet, uint16_t timeout, bool sendAck)
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

    bool isDuplicate = _ack.isDuplicate(packet);

    if (sendAck)
    {
        Packet ackPacket;
        Ack::make(ackPacket, packet.counter);
        sendOnce(ackPacket);
    }

    return Result::OK;
}

Result Link::send(Packet& packet)
{
    return sendPacket(packet);
}

Result Link::receive(Packet& packet)
{
    return receivePacket(packet, LINK_TIMEOUT, true);
}

Result Link::sendOnce(Packet& packet)
{
    uint16_t written = 0;
    Result result = Serializer::serialize(packet, _buffer, sizeof(_buffer), written);
    if (result != Result::OK)
        return result;

    result = _radio.send(_buffer, written);
    return result;
}

Result Link::waitForAck(uint16_t counter, uint16_t timeout)
{
    Packet incoming;
    Result result = receivePacket(incoming, timeout, false);

    if (result == Result::OK)
    {
        if (_ack.isAckFor(incoming, counter))
            return Result::OK;
        else
            return Result::ACK_MISMATCH;
    }

    return Result::TIMEOUT;
}

Result Link::readByte(uint8_t& value, uint32_t deadline)
{
    while (!_radio.available())
    {
        if (millis() >= deadline)
            return Result::TIMEOUT;
        delay(1);
    }

    if (_radio.receive(&value, 1) == 1)
        return Result::OK;
    else
        return Result::NOT_READY;
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

    const uint8_t payloadLength = _buffer[6];
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