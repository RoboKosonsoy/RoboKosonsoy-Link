#ifndef RKL_RESULT_H
#define RKL_RESULT_H

/*
 * RoboKosonsoy Link (RKL)
 * Result codes
 *
 * Copyright (c) RoboKosonsoy Community
 * Licensed under the MIT License
 */

#include <Arduino.h>

namespace RKL
{

enum class Result : uint8_t
{
    OK = 0,

    TIMEOUT,

    NOT_READY,

    INVALID_PARAMETER,

    BUFFER_OVERFLOW,

    CRC_ERROR,

    SERIAL_ERROR,

    CONFIG_ERROR,

    UNKNOWN_ERROR
};

} // namespace RKL

#endif // RKL_RESULT_H