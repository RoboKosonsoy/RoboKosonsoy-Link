#include <SoftwareSerial.h>
#include <RKL.h>

SoftwareSerial Radio(10, 11);

RKL::E32 e32(
    Radio,
    2,
    3,
    4
);

RKL::Link link(e32);

void setup()
{
    Serial.begin(115200);
    Radio.begin(9600);

    Serial.println();
    Serial.println("=== Packet Receiver ===");

    if (e32.begin() != RKL::Result::OK)
    {
        Serial.println("E32 INIT ERROR");
        while (1);
    }

    Serial.println("E32 READY");
}

void loop()
{
    RKL::Packet packet;

    RKL::Result result = link.receive(packet);

    if (result == RKL::Result::OK)
    {
        Serial.println("-----");
        Serial.print("SEQ: ");
        Serial.println(packet.id);

        Serial.print("TYPE: ");
        Serial.println((uint8_t)packet.type);

        Serial.print("LEN: ");
        Serial.println(packet.length);

        Serial.print("DATA: ");

        for (uint8_t i = 0; i < packet.length; i++)
            Serial.write(packet.payload[i]);

        Serial.println();
        Serial.println("CRC OK");
    }
}