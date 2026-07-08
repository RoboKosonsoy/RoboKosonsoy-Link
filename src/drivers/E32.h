#ifndef RKL_E32_H
#define RKL_E32_H

#include <Arduino.h>

#include "Radio.h"
#include "E32_Config.h"

namespace RKL
{

class E32 : public Radio
{
public:

    E32(Stream& serial,
        uint8_t auxPin,
        uint8_t m0Pin,
        uint8_t m1Pin);

    Result begin() override;

    bool available() override;

    Result send(const uint8_t* data, size_t length) override;

    size_t receive(uint8_t* buffer, size_t length) override;

    Result waitReady(uint16_t timeout = 500) override;

    bool readConfiguration(E32Config& config);

    bool writeConfiguration(const E32Config& config);

    bool getVersion(uint8_t version[4]);

    void setNormalMode();

    void setProgramMode();

private:

    Stream& _serial;

    uint8_t _auxPin;
    uint8_t _m0Pin;
    uint8_t _m1Pin;
};

}

#endif