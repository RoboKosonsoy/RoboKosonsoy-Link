#ifndef RKL_RADIO_H
#define RKL_RADIO_H

/*
 * RoboKosonsoy Link (RKL)
 * Abstract Radio Interface
 *
 * Copyright (c) RoboKosonsoy Community
 * Licensed under the MIT License
 */

#include <Arduino.h>

namespace RKL
{

class Radio
{
public:

    virtual ~Radio() = default;

    virtual bool begin(uint32_t baudrate = 9600) = 0;

    virtual bool available() = 0;

    virtual size_t send(const uint8_t* data, size_t length) = 0;

    virtual size_t receive(uint8_t* buffer, size_t length) = 0;

    virtual bool waitReady(uint16_t timeout = 500) = 0;
};

} // namespace RKL

#endif // RKL_RADIO_H