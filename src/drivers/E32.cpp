#include "E32.h"
#include "../core/Debug.h"   // <-- добавлено для отладки

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
    // Проверяем готовность перед отправкой (один раз)
    Result r = waitReady();
    if (r != Result::OK)
        return r;

#if RKL_DEBUG
    Serial.println();
    Serial.println("===== E32 SEND =====");
    Serial.print("LEN: ");
    Serial.println(length);
    Serial.print("HEX: ");
    RKL_DebugHex(data, length);
#endif

    // Отправка
    if (_serial.write(data, length) != length)
        return Result::SERIAL_ERROR;

    _serial.flush();

    // Не ждём повторно ready, так как данные уже в буфере UART
    // (но можно оставить, если нужно убедиться, что модуль обработал)
    // Для надёжности оставим, но уберём лишний waitReady.
    // Мы уже проверили ready до отправки, поэтому возвращаем OK.
    return Result::OK;
}

size_t E32::receive(uint8_t* buffer, size_t length)
{
    if (buffer == nullptr || length == 0)
        return 0;

    size_t count = 0;
    while (_serial.available() > 0 && count < length)
    {
        int value = _serial.read();
        if (value < 0)
            break;
        buffer[count++] = static_cast<uint8_t>(value);
    }
    return count;
}

Result E32::waitReady(uint16_t timeout)
{
    uint32_t start = millis();
    while (digitalRead(_auxPin) == LOW)
    {
        if (millis() - start >= timeout)
            return Result::TIMEOUT;
        // Небольшая задержка для снижения нагрузки (можно убрать)
        delay(1);
    }
    return Result::OK;
}

void E32::setNormalMode()
{
    digitalWrite(_m0Pin, LOW);
    digitalWrite(_m1Pin, LOW);
    delay(40); // небольшая задержка для переключения
}

void E32::setProgramMode()
{
    digitalWrite(_m0Pin, HIGH);
    digitalWrite(_m1Pin, HIGH);
    delay(40);
}

bool E32::readConfiguration(E32Config& cfg)
{
    setProgramMode();
    uint8_t cmd[3] = {0xC1, 0xC1, 0xC1};
    _serial.write(cmd, 3);
    _serial.flush();

    if (waitReady() != Result::OK)
    {
        setNormalMode();
        return false;
    }

    uint32_t t = millis();
    while (_serial.available() < 6)
    {
        if (millis() - t > 500)
        {
            setNormalMode();
            return false;
        }
        delay(1);
    }

    uint8_t rx[6];
    _serial.readBytes(rx, 6);
    cfg.addh = rx[1];
    cfg.addl = rx[2];
    cfg.sped = rx[3];
    cfg.chan = rx[4];
    cfg.option = rx[5];

    setNormalMode();
    return true;
}

bool E32::writeConfiguration(const E32Config& cfg)
{
    setProgramMode();
    uint8_t tx[6] = {
        0xC0,
        cfg.addh,
        cfg.addl,
        cfg.sped,
        cfg.chan,
        cfg.option
    };
    _serial.write(tx, 6);
    _serial.flush();

    if (waitReady() != Result::OK)
    {
        setNormalMode();
        return false;
    }

    setNormalMode();
    return true;
}

bool E32::getVersion(uint8_t version[4])
{
    setProgramMode();
    uint8_t cmd[3] = {0xC3, 0xC3, 0xC3};
    _serial.write(cmd, 3);
    _serial.flush();

    if (waitReady() != Result::OK)
    {
        setNormalMode();
        return false;
    }

    uint32_t t = millis();
    while (_serial.available() < 4)
    {
        if (millis() - t > 500)
        {
            setNormalMode();
            return false;
        }
        delay(1);
    }

    _serial.readBytes(version, 4);
    setNormalMode();
    return true;
}

} // namespace RKL