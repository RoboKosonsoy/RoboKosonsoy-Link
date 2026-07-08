#include "E32.h"

namespace RKL
{

E32::E32(Stream& serial,
         uint8_t auxPin,
         uint8_t m0Pin,
         uint8_t m1Pin)
    : _serial(serial),
      _auxPin(auxPin),
      _m0Pin(m0Pin),
      _m1Pin(m1Pin)
{
}

Result E32::begin()
{
    pinMode(_auxPin, INPUT);

    pinMode(_m0Pin, OUTPUT);
    pinMode(_m1Pin, OUTPUT);

    setNormalMode();

    return waitReady();
}

bool E32::available()
{
    return _serial.available() > 0;
}

Result E32::send(const uint8_t* data, size_t length)
{
    Result r = waitReady();

    if (r != Result::OK)
        return r;

    size_t written = _serial.write(data, length);

    if (written != length)
        return Result::SERIAL_ERROR;

    _serial.flush();

    return waitReady();
}

size_t E32::receive(uint8_t* buffer, size_t length)
{
    return _serial.readBytes(buffer, length);
}

Result E32::waitReady(uint16_t timeout)
{
    unsigned long start = millis();

    while (digitalRead(_auxPin) == LOW)
    {
        if (millis() - start >= timeout)
            return Result::TIMEOUT;

        delay(1);
    }

    return Result::OK;
}

void E32::setNormalMode()
{
    digitalWrite(_m0Pin, LOW);
    digitalWrite(_m1Pin, LOW);

    delay(40);
}

void E32::setProgramMode()
{
    digitalWrite(_m0Pin, HIGH);
    digitalWrite(_m1Pin, HIGH);

    delay(40);
}

}