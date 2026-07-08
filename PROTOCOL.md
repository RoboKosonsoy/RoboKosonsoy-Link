# RoboKosonsoy Link Protocol Specification

Version: 1.0 (Draft)

---

# Overview

RoboKosonsoy Link (RKL) uses a binary packet-based protocol designed for reliable, low-latency communication over LoRa radio modules.

The protocol is optimized for:

* RC aircraft
* Ground robots
* Telemetry
* Educational robotics
* Embedded systems

---

# Packet Format

| Offset | Field            | Size (bytes) |
| -----: | ---------------- | -----------: |
|      0 | Start Byte       |            1 |
|      1 | Protocol Version |            1 |
|      2 | Packet Type      |            1 |
|      3 | Flags            |            1 |
|    4-5 | Packet Counter   |            2 |
|      6 | Payload Length   |            1 |
|   7... | Payload          |         0–48 |
|    n-2 | CRC16 High       |            1 |
|    n-1 | CRC16 Low        |            1 |

---

# Start Byte

Value:

0xAA

Used to identify the beginning of a packet.

---

# Protocol Version

Current version:

1

Allows future protocol compatibility.

---

# Packet Types

| ID   | Description   |
| ---- | ------------- |
| 0x01 | RC Control    |
| 0x02 | ACK           |
| 0x03 | Ping          |
| 0x04 | Telemetry     |
| 0x05 | Configuration |
| 0x06 | Heartbeat     |
| 0x07 | Debug         |

---

# Flags

Reserved for future use.

Possible functions:

* ACK Required
* Encrypted Packet
* Emergency Packet

---

# Packet Counter

16-bit unsigned integer.

Incremented for every transmitted packet.

Used for:

* Duplicate detection
* Packet loss detection
* RTT calculation

---

# Payload

Maximum payload size:

48 bytes

---

# CRC

CRC16-CCITT

Polynomial:

0x1021

Initial value:

0xFFFF

---

# RC Payload

Eight channels.

Each channel:

uint16_t

Range:

1000–2000

Channel mapping:

CH1 Roll

CH2 Pitch

CH3 Throttle

CH4 Yaw

CH5 AUX1

CH6 AUX2

CH7 AUX3

CH8 AUX4

---

# Telemetry Payload

Planned fields:

* Battery voltage
* RSSI
* Temperature
* Link quality
* Flight mode
* User data

---

# Future Extensions

Reserved packet identifiers allow adding:

* Firmware update
* GPS
* IMU data
* Mission control
* Ground station commands

without breaking compatibility.
