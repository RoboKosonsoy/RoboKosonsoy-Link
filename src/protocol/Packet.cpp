#include "Packet.h"

namespace RKL
{

bool Packet::calculateCRC()
{
    crc = CRC16::calculate(
        reinterpret_cast<uint8_t*>(&type),
        3 + length
    );

    return true;
}

bool Packet::checkCRC()
{
    return crc == CRC16::calculate(
        reinterpret_cast<uint8_t*>(&type),
        3 + length
    );
}

}