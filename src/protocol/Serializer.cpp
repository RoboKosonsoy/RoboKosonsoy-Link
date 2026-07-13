#include "Serializer.h"
#include "../core/CRC16.h"

namespace RKL
{

Result Serializer::serialize(Packet& packet,
                             uint8_t* buffer,
                             uint16_t bufferSize,
                             uint16_t& written)
{
    written = 0;
    if (buffer == nullptr || packet.length > MAX_PAYLOAD_SIZE)
        return Result::INVALID_PARAMETER;

    const uint16_t size = packet.packetSize();
    if (size > bufferSize || size > MAX_PACKET_SIZE)
        return Result::BUFFER_OVERFLOW;

    buffer[0] = START_BYTE;
    buffer[1] = packet.version;
    buffer[2] = static_cast<uint8_t>(packet.type);
    buffer[3] = packet.flags;
    buffer[4] = static_cast<uint8_t>(packet.counter >> 8);
    buffer[5] = static_cast<uint8_t>(packet.counter & 0xFF);
    buffer[6] = packet.length;

    if (packet.length > 0)
        memcpy(buffer + PACKET_HEADER_SIZE, packet.payload, packet.length);

    uint8_t crcBuffer[MAX_PACKET_SIZE];
    crcBuffer[0] = packet.version;
    crcBuffer[1] = static_cast<uint8_t>(packet.type);
    crcBuffer[2] = packet.flags;
    crcBuffer[3] = static_cast<uint8_t>(packet.counter >> 8);
    crcBuffer[4] = static_cast<uint8_t>(packet.counter & 0xFF);
    crcBuffer[5] = packet.length;
    if (packet.length > 0)
        memcpy(crcBuffer + 6, packet.payload, packet.length);

    packet.crc = CRC16::calculate(crcBuffer, 6 + packet.length);

    buffer[PACKET_HEADER_SIZE + packet.length] = static_cast<uint8_t>(packet.crc >> 8);
    buffer[PACKET_HEADER_SIZE + packet.length + 1] = static_cast<uint8_t>(packet.crc & 0xFF);

    written = size;

#if RKL_DEBUG
    RKL_LOGLN("");
    RKL_LOGLN("========== TX FRAME ==========");
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