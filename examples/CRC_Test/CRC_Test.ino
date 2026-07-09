#include <RKL.h>

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    const char text[] = "RoboKosonsoy";
    const uint16_t crc = RKL::CRC16::calculate(
        reinterpret_cast<const uint8_t*>(text),
        sizeof(text) - 1);

    Serial.println("=== RKL CRC Test ===");
    Serial.print("CRC16: 0x");
    Serial.println(crc, HEX);

    if (RKL::CRC16::verify(reinterpret_cast<const uint8_t*>(text), sizeof(text) - 1, crc))
        Serial.println("Verification: OK");
    else
        Serial.println("Verification: ERROR");
}

void loop()
{
}
