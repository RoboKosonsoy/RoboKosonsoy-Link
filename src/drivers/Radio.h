#ifndef RKL_RADIO_H
#define RKL_RADIO_H

#include <Arduino.h>
#include "../core/Result.h"

namespace RKL
{

class Radio
{
public:

    virtual ~Radio() = default;

    /** @brief Initialize the radio driver and hardware pins. */
    virtual Result begin() = 0;

    /** @brief Return true when at least one byte can be read. */
    virtual bool available() = 0;

    /** @brief Send a raw byte frame. */
    virtual Result send(const uint8_t* data, size_t length) = 0;

    /** @brief Read currently available bytes into buffer. */
    virtual size_t receive(uint8_t* buffer, size_t length) = 0;

    /** @brief Wait until the hardware reports ready or timeout expires. */
    virtual Result waitReady(uint16_t timeout = 500) = 0;
};

}

#endif
