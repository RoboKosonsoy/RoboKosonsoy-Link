#ifndef RKL_RESULT_H
#define RKL_RESULT_H

#include <Arduino.h>

namespace RKL
{

enum class Result : uint8_t
{
    OK = 0,

    TIMEOUT,

    SERIAL_ERROR,

    CRC_ERROR,

    INVALID_PARAMETER,

    BUFFER_OVERFLOW,

    CONFIG_ERROR,

    NOT_READY,

    UNKNOWN_ERROR
};

}

#endif