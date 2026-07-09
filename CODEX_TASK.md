# RoboKosonsoy-Link — Sprint 3

## Goal

Refactor the entire library into a clean production-quality architecture.

Do NOT rewrite the project from scratch.

Keep compatibility with Arduino Nano (ATmega328P).

Radio module:
- EBYTE E32-433T30D

Language:
- C++17 compatible with Arduino framework.

---

## Requirements

Create or refactor:

src/
    core/
        CRC16.*
        Config.*
        Types.*
        Result.*
        Error.*

    drivers/
        Radio.h
        E32.h
        E32.cpp
        E32_Config.*

    protocol/
        Packet.*
        Link.*
        Serializer.*
        Parser.*
        Ack.*
        Retry.*

examples/
    E32_Test
    Packet_Test

---

## Packet

Packet must contain:

start byte
packet type
sequence id
payload length
payload
crc16

Serialization/deserialization required.

CRC16 verification required.

---

## Link

Implement

sendPacket()

receivePacket()

automatic CRC verification

timeout support

---

## ACK

Implement ACK packets.

Sequence numbers.

Duplicate packet detection.

---

## Retry

Automatic resend.

Configurable retry count.

Configurable timeout.

---

## Code Style

Modern C++.

No dynamic allocation.

No String.

No exceptions.

Small RAM usage.

Arduino Nano compatible.

---

## Documentation

Update README.

Update ARCHITECTURE.md.

Generate Doxygen comments.

---

## Tests

Packet_Test

E32_Test

CRC_Test

All examples must compile.

No breaking changes.
