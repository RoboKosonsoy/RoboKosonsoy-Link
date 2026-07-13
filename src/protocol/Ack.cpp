#include "Ack.h"

namespace RKL
{

Ack::Ack() : _hasLastCounter(false), _lastCounter(0) {}

void Ack::reset()
{
    _hasLastCounter = false;
    _lastCounter = 0;
}

bool Ack::isAckFor(const Packet& ackPacket, uint16_t counter) const
{
    return ackPacket.type == PacketType::ACK &&
           ackPacket.counter == counter &&
           ackPacket.length == 0;
}

bool Ack::isDuplicate(const Packet& packet)
{
    if (packet.type == PacketType::ACK)
        return false;

    if (_hasLastCounter && packet.counter == _lastCounter)
        return true;

    _hasLastCounter = true;
    _lastCounter = packet.counter;
    return false;
}

void Ack::make(Packet& packet, uint16_t counter)
{
    packet.clear();
    packet.type = PacketType::ACK;
    packet.counter = counter;
    packet.length = 0;
    packet.calculateCRC();
}

} // namespace RKL