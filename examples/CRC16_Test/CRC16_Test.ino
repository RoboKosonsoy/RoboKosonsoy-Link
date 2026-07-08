#include <RKL.h>

void setup()
{
    Serial.begin(115200);

    while (!Serial);

    const char text[] = "RoboKosonsoy";

    uint16_t crc = RKL::CRC16::calculate(
        (const uint8_t*)text,
        sizeof(text) - 1);

    Serial.println("================================");
    Serial.println(" RoboKosonsoy Link CRC16 Test");
    Serial.println("================================");

    Serial.print("Text : ");
    Serial.println(text);

    Serial.print("CRC16: 0x");
    Serial.println(crc, HEX);

    if (RKL::CRC16::verify(
            (const uint8_t*)text,
            sizeof(text) - 1,
            crc))
    {
        Serial.println("Verification: SUCCESS");
    }
    else
    {
        Serial.println("Verification: FAILED");
    }
}

void loop()
{
}