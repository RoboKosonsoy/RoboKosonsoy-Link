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
    virtual Result begin() = 0;
    virtual bool available() = 0;
    virtual Result send(const uint8_t* data, size_t length) = 0;
    virtual size_t receive(uint8_t* buffer, size_t length) = 0;
    virtual Result waitReady(uint16_t timeout = 500) = 0;
};

} // namespace RKL

#endif