#include <RKL.h>
#include <SoftwareSerial.h>

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

    if (e32.begin() == RKL::Result::OK)
    {
        Serial.println("E32 Ready");
    }
    else
    {
        Serial.println("E32 Error");
    }
}

void loop()
{
}