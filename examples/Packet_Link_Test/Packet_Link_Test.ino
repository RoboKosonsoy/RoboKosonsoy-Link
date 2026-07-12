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

uint8_t sequence = 0;

void setup()
{
    Serial.begin(115200);
    Radio.begin(9600);

    Serial.println();
    Serial.println("=== Packet Link Test ===");

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

    packet.clear();

    packet.type = RKL::PacketType::RC_CONTROL;
    packet.id = sequence++;
    packet.length = 5;

    memcpy(packet.payload, "HELLO", 5);

    RKL::Result result = link.send(packet);

    Serial.print("SEQ: ");
    Serial.print(packet.id);

    Serial.print("  CRC: ");
    Serial.print(packet.crc, HEX);

    Serial.print("  RESULT: ");
    Serial.println(static_cast<int>(result));

    delay(1000);
}