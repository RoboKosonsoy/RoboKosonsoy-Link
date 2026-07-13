# RoboKosonsoy Link Protocol Specification

Version: 1.0 (Draft) – соответствует реализации с 7-байтовым заголовком.

---

## Overview

RoboKosonsoy Link (RKL) uses a binary packet-based protocol designed for reliable, low-latency communication over LoRa radio modules.

The protocol is optimized for:

* RC aircraft
* Ground robots
* Telemetry
* Educational robotics
* Embedded systems

---

## Packet Format

| Offset | Field            | Size (bytes) | Description                         |
|--------|------------------|--------------|-------------------------------------|
| 0      | Start Byte       | 1            | Always `0xAA`                       |
| 1      | Protocol Version | 1            | Current version = `1`               |
| 2      | Packet Type      | 1            | See table below                     |
| 3      | Flags            | 1            | Reserved for future use             |
| 4–5    | Packet Counter   | 2            | 16‑bit unsigned, increments per packet |
| 6      | Payload Length   | 1            | Number of payload bytes (0–48)      |
| 7...   | Payload          | 0–48         | Application data                    |
| n-2    | CRC16 High       | 1            | CRC16‑CCITT (MSB)                   |
| n-1    | CRC16 Low        | 1            | CRC16‑CCITT (LSB)                   |

**Total packet size** = 7 + payload_length + 2 (CRC)  = from 9 to 57 bytes.

---

## Start Byte

Value: `0xAA`

Used to identify the beginning of a packet.

---

## Protocol Version

Current version: `1`

Allows future protocol extensions while maintaining backward compatibility.

---

## Packet Types

| ID   | Description   |
|------|---------------|
| 0x01 | RC Control    |
| 0x02 | ACK           |
| 0x03 | Ping          |
| 0x04 | Telemetry     |
| 0x05 | Configuration |
| 0x06 | Heartbeat     |
| 0x07 | Debug         |
| 0x08 | NACK (reserved) |

---

## Flags

Reserved for future use. Possible functions:

* ACK Required
* Encrypted Packet
* Emergency Packet

Currently all flags are set to `0`.

---

## Packet Counter

16‑bit unsigned integer. Incremented for every transmitted packet (except ACK packets – they carry the counter of the packet they acknowledge).

Used for:

* Duplicate detection
* Packet loss detection
* RTT calculation

---

## Payload

Maximum payload size: **48 bytes**

---

## CRC

CRC16‑CCITT

* Polynomial: `0x1021`
* Initial value: `0xFFFF`
* Coverage: bytes 1..6 (version, type, flags, counter_hi, counter_lo, length) + payload

---

## RC Payload (for type 0x01)

Eight channels, each `uint16_t`, range 1000–2000.

| Channel | Function |
|---------|----------|
| CH1     | Roll     |
| CH2     | Pitch    |
| CH3     | Throttle |
| CH4     | Yaw      |
| CH5     | AUX1     |
| CH6     | AUX2     |
| CH7     | AUX3     |
| CH8     | AUX4     |

---

## Telemetry Payload (planned)

* Battery voltage
* RSSI
* Temperature
* Link quality
* Flight mode
* User data

---

## Future Extensions

Reserved packet identifiers and flags allow adding:

* Firmware update
* GPS data
* IMU data
* Mission control
* Ground station commands

without breaking compatibility.