#include <SoftwareSerial.h>
#include <RKL.h>

SoftwareSerial Radio(10, 11);

RKL::E32 e32(Radio, 2, 3, 4);
RKL::Link link(e32);

uint16_t sequence = 0;

void setup()
{
    Serial.begin(115200);
    Radio.begin(9600);

    Serial.println();
    Serial.println("=== RTT Measurement (7-byte header) ===");

    if (e32.begin() != RKL::Result::OK)
    {
        Serial.println("E32 INIT ERROR");
        while (1);
    }

    Serial.println("E32 READY");
    Serial.println("SEQ\tRTT(ms)\tRESULT");
}

void loop()
{
    RKL::Packet packet;
    packet.clear();

    packet.type = RKL::PacketType::RC_CONTROL;
    packet.counter = sequence++;
    packet.length = 5;
    memcpy(packet.payload, "HELLO", 5);
    packet.calculateCRC();

    unsigned long startTime = millis();
    RKL::Result result = link.send(packet);
    unsigned long rtt = millis() - startTime;

    Serial.print(sequence - 1);
    Serial.print("\t");
    Serial.print(rtt);
    Serial.print("\t");
    Serial.println(static_cast<int>(result));

    delay(1000);
}