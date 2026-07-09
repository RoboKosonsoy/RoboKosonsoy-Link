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
    PacketType type = PacketType::RC_CONTROL;
    uint8_t id = 0;
    uint8_t length = 0;

    uint8_t payload[MAX_PAYLOAD_SIZE];

    uint16_t crc = 0;

    /** @brief Reset packet fields and clear payload storage. */
    void clear();

    /** @brief Calculate and store CRC16 over type, sequence, length and payload. */
    bool calculateCRC();

    /** @brief Verify the stored CRC16. */
    bool checkCRC() const;

    /** @brief Total serialized packet size in bytes. */
    uint16_t packetSize() const;

    /** @brief Set packet payload from a fixed byte buffer. */
    Result setPayload(const uint8_t* data, uint8_t size);

    /** @brief Compatibility wrapper around Serializer. */
    bool serialize(uint8_t* buffer) const;

    /** @brief Compatibility wrapper around Parser. */
    bool deserialize(const uint8_t* buffer, uint16_t size);
};

}

#endif
