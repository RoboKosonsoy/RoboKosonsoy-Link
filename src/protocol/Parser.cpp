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

    const uint8_t payloadLength = buffer[3];

    if (payloadLength > MAX_PAYLOAD_SIZE)
        return Result::BUFFER_OVERFLOW;

    const uint16_t expectedSize = PACKET_HEADER_SIZE + payloadLength + CRC_SIZE;

    if (size != expectedSize)
        return Result::INVALID_PACKET;

    const uint16_t receivedCrc =
        (static_cast<uint16_t>(buffer[PACKET_HEADER_SIZE + payloadLength]) << 8) |
        buffer[PACKET_HEADER_SIZE + payloadLength + 1];

    if (!CRC16::verify(buffer + 1, 3 + payloadLength, receivedCrc))
        return Result::CRC_ERROR;

    packet.clear();
    packet.start = buffer[0];
    packet.type = static_cast<PacketType>(buffer[1]);
    packet.id = buffer[2];
    packet.length = payloadLength;

    if (payloadLength > 0)
        memcpy(packet.payload, buffer + PACKET_HEADER_SIZE, payloadLength);

    packet.crc = receivedCrc;
    return Result::OK;
}

} // namespace RKL
