#ifndef RKL_PACKET_H
#define RKL_PACKET_H

#include <Arduino.h>

namespace RKL
{

constexpr uint8_t PACKET_START = 0xAA;
constexpr uint8_t MAX_PAYLOAD = 48;

struct Packet
{
    uint8_t start = PACKET_START;
    uint8_t type = 0;
    uint8_t length = 0;
    uint8_t payload[MAX_PAYLOAD];
    uint16_t crc = 0;
};

}

#endif