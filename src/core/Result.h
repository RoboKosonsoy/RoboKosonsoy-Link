#ifndef RKL_RESULT_H
#define RKL_RESULT_H

#include <Arduino.h>

namespace RKL
{

/**
 * @brief Small status code used across the library.
 */
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
    INVALID_PACKET,
    DUPLICATE_PACKET,
    ACK_MISMATCH,
    RETRY_EXHAUSTED,
    UNKNOWN_ERROR
};

} // namespace RKL

#endif // RKL_RESULT_H
