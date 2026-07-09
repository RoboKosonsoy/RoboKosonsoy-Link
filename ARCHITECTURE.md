# RoboKosonsoy Link Architecture

## Overview

RoboKosonsoy Link (RKL) is a layered Arduino communication library for reliable radio packets over EBYTE E32 modules.

```text
Application
  -> RKL Link Protocol
  -> Radio Driver Interface
  -> EBYTE E32-433T30D
```

## Design Principles

* Modular architecture
* Clear separation of responsibilities
* Hardware abstraction
* No dynamic allocation
* No `String`
* No exceptions
* Small RAM usage for Arduino Nano / ATmega328P
* C++17 compatible with the Arduino framework

## Layer 0 - Core

Shared definitions and small primitives.

Files:

```text
src/core/CRC16.h
src/core/CRC16.cpp
src/core/Config.h
src/core/Types.h
src/core/Result.h
src/core/Error.h
```

Responsibilities:

* CRC16-CCITT calculation and verification
* Protocol constants and packet limits
* Packet, radio and link enums
* Lightweight result/error reporting

## Layer 1 - Drivers

Hardware-facing radio abstractions.

Files:

```text
src/drivers/Radio.h
src/drivers/E32.h
src/drivers/E32.cpp
src/drivers/E32_Config.h
src/drivers/E32_Config.cpp
```

Responsibilities:

* Abstract raw radio send/receive operations
* Initialize and control E32 pins
* Switch E32 normal/program modes
* Read/write E32 configuration
* Wait for AUX readiness

## Layer 2 - Protocol

Reliable packet transport over a `Radio` implementation.

Files:

```text
src/protocol/Packet.h
src/protocol/Packet.cpp
src/protocol/Serializer.h
src/protocol/Serializer.cpp
src/protocol/Parser.h
src/protocol/Parser.cpp
src/protocol/Ack.h
src/protocol/Ack.cpp
src/protocol/Retry.h
src/protocol/Retry.cpp
src/protocol/Link.h
src/protocol/Link.cpp
```

Packet format:

```text
start byte | packet type | sequence id | payload length | payload | crc16
```

CRC16 covers `packet type`, `sequence id`, `payload length` and `payload`.

Responsibilities:

* Packet creation
* Serialization and deserialization
* CRC verification
* Sequence numbers
* ACK packets
* Duplicate packet detection
* Configurable retry count and timeout
* Timeout-aware `sendPacket()` and `receivePacket()`

## Layer 3 - Application

User sketches and higher-level applications.

Examples:

```text
examples/CRC_Test
examples/CRC16_Test
examples/E32_Test
examples/Packet_Test
```

## Supported Platforms

Current:

* Arduino Nano
* Arduino Uno
* ESP32

## Supported Radio Modules

Current:

* EBYTE E32-433T30D

Planned:

* SX1276
* SX1278
