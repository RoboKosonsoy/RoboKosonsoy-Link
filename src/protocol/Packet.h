#ifndef RKL_PACKET_H
#define RKL_PACKET_H

#include <Arduino.h>

#include "../core/Config.h"
#include "../core/Types.h"
#include "../core/CRC16.h"

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

    bool calculateCRC();
    bool checkCRC();

    uint16_t size() const
    {
        return 6 + length;
    }
};

}

#endif