#include "Ack.h"

namespace RKL
{

Ack::Ack() : _hasLastSequence(false), _lastSequence(0) {}

void Ack::reset()
{
    _hasLastSequence = false;
    _lastSequence = 0;
}

bool Ack::isAckFor(const Packet& ackPacket, uint8_t sequence) const
{
    return ackPacket.type == PacketType::ACK &&
           ackPacket.id == sequence &&
           ackPacket.length == 0;
}

bool Ack::isDuplicate(const Packet& packet)
{
    if (packet.type == PacketType::ACK)
        return false;

    if (_hasLastSequence && packet.id == _lastSequence)
        return true;

    _hasLastSequence = true;
    _lastSequence = packet.id;
    return false;
}

void Ack::make(Packet& packet, uint8_t sequence)
{
    packet.clear();
    packet.type = PacketType::ACK;
    packet.id = sequence;
    packet.length = 0;
    packet.calculateCRC();
}

} // namespace RKL