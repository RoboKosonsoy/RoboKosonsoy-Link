#ifndef RKL_PACKET_H
#define RKL_PACKET_H

#include <Arduino.h>
#include "../core/Config.h"
#include "../core/Types.h"
#include "../core/Result.h"

namespace RKL
{

struct Packet
{
    uint8_t start = START_BYTE;
    uint8_t version = PROTOCOL_VERSION;
    PacketType type = PacketType::RC_CONTROL;
    uint8_t flags = 0;
    uint16_t counter = 0;
    uint8_t length = 0;
    uint8_t payload[MAX_PAYLOAD_SIZE];
    uint16_t crc = 0;

    void clear();
    bool calculateCRC();
    bool checkCRC() const;
    uint16_t packetSize() const;
    Result setPayload(const uint8_t* data, uint8_t size);
    bool serialize(uint8_t* buffer) const;
    bool deserialize(const uint8_t* buffer, uint16_t size);
};

} // namespace RKL

#endif