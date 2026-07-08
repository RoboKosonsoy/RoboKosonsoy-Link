#include <SoftwareSerial.h>
#include <RKL.h>

SoftwareSerial Radio(10, 11);

RKL::E32 e32(
    Radio,
    2,   // AUX
    3,   // M0
    4    // M1
);

void setup()
{
    Serial.begin(115200);
    Radio.begin(9600);

    Serial.println();
    Serial.println("=== RKL E32 Test ===");

    if (e32.begin() != RKL::Result::OK)
    {
        Serial.println("E32 INIT ERROR");
        return;
    }

    Serial.println("E32 READY");

    RKL::E32Config cfg;

    if (e32.readConfiguration(cfg))
    {
        Serial.println("CONFIG:");

        Serial.print("ADDH: 0x");
        Serial.println(cfg.addh, HEX);

        Serial.print("ADDL: 0x");
        Serial.println(cfg.addl, HEX);

        Serial.print("SPED: 0x");
        Serial.println(cfg.sped, HEX);

        Serial.print("CHAN: 0x");
        Serial.println(cfg.chan, HEX);

        Serial.print("OPTION: 0x");
        Serial.println(cfg.option, HEX);
    }
    else
    {
        Serial.println("READ CONFIG FAILED");
    }

    uint8_t version[4];

    if (e32.getVersion(version))
    {
        Serial.println("VERSION:");

        for (uint8_t i = 0; i < 4; i++)
        {
            Serial.print("0x");
            Serial.print(version[i], HEX);
            Serial.print(' ');
        }

        Serial.println();
    }
    else
    {
        Serial.println("READ VERSION FAILED");
    }
}

void loop()
{
}