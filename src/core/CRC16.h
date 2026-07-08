#ifndef RKL_CRC16_H
#define RKL_CRC16_H

/*
 * RoboKosonsoy Link (RKL)
 * CRC16-CCITT
 *
 * Copyright (c) RoboKosonsoy Community
 * Licensed under the MIT License
 */

#include <Arduino.h>

namespace RKL
{

class CRC16
{
public:

    static uint16_t calculate(const uint8_t* data, size_t length);

    static bool verify(
        const uint8_t* data,
        size_t length,
        uint16_t expected);

};

} // namespace RKL

#endif // RKL_CRC16_H