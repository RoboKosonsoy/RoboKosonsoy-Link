#include "Packet.h"
#include "../core/CRC16.h"
#include "Parser.h"
#include "Serializer.h"

namespace RKL
{

void Packet::clear()
{
    start = START_BYTE;
    type = PacketType::RC_CONTROL;
    id = 0;
    length = 0;
    crc = 0;
    memset(payload, 0, sizeof(payload));
}

bool Packet::calculateCRC()
{
    if (length > MAX_PAYLOAD_SIZE)
        return false;

    uint8_t buffer[MAX_PACKET_SIZE];
    buffer[0] = static_cast<uint8_t>(type);
    buffer[1] = id;
    buffer[2] = length;

    if (length > 0)
        memcpy(buffer + 3, payload, length);

    crc = CRC16::calculate(buffer, 3 + length);
    return true;
}

bool Packet::checkCRC() const
{
    if (length > MAX_PAYLOAD_SIZE)
        return false;

    uint8_t buffer[MAX_PACKET_SIZE];
    buffer[0] = static_cast<uint8_t>(type);
    buffer[1] = id;
    buffer[2] = length;

    if (length > 0)
        memcpy(buffer + 3, payload, length);

    return CRC16::verify(buffer, 3 + length, crc);
}

uint16_t Packet::packetSize() const
{
    return PACKET_HEADER_SIZE + length + CRC_SIZE; // 4 + length + 2
}

Result Packet::setPayload(const uint8_t* data, uint8_t size)
{
    if (size > MAX_PAYLOAD_SIZE)
        return Result::BUFFER_OVERFLOW;
    if (size > 0 && data == nullptr)
        return Result::INVALID_PARAMETER;

    length = size;
    memset(payload, 0, sizeof(payload));
    if (size > 0)
        memcpy(payload, data, size);
    return Result::OK;
}

bool Packet::serialize(uint8_t* buffer) const
{
    Packet copy = *this;
    uint16_t written = 0;
    return Serializer::serialize(copy, buffer, MAX_PACKET_SIZE, written) == Result::OK;
}

bool Packet::deserialize(const uint8_t* buffer, uint16_t size)
{
    return Parser::parse(buffer, size, *this) == Result::OK;
}

} // namespace RKL