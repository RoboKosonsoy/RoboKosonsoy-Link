# RoboKosonsoy Link Architecture

## Overview

RoboKosonsoy Link (RKL) is designed as a layered communication library. Each layer has a single responsibility, making the project easy to maintain, extend, and test.

```
Application
      │
      ▼
RKL Protocol
      │
      ▼
Radio Driver
      │
      ▼
EBYTE E32 Module
```

---

# Design Principles

* Modular architecture
* Clear separation of responsibilities
* Hardware abstraction
* Platform independence
* Low latency
* High reliability
* Easy debugging
* Educational code style

---

# Library Layers

## Layer 1 – Radio Driver

Responsible for direct communication with supported radio modules.

Responsibilities:

* Configure E32 modules
* Read/write configuration
* Send raw bytes
* Receive raw bytes
* Switch operating modes
* Wait for AUX
* Detect communication errors

Files:

```
RKLE32.h
RKLE32.cpp
```

---

## Layer 2 – RKL Protocol

Provides a reliable communication protocol over the radio driver.

Responsibilities:

* Packet creation
* Packet parsing
* CRC16 verification
* Packet counters
* ACK
* Retransmission
* Failsafe
* Connection monitoring

Files:

```
RKL_Link.h
RKL_Link.cpp
RKL_Packet.h
```

---

## Layer 3 – Application

User application.

Examples:

* RC transmitter
* RC receiver
* Robot control
* Telemetry
* Ground station

---

# Project Structure

```
src/
examples/
docs/
hardware/
tests/
```

---

# Supported Platforms

Current:

* Arduino Nano
* Arduino Uno
* ESP32

Future:

* STM32
* RP2040

---

# Supported Radio Modules

Current:

* EBYTE E32-433T30D

Planned:

* SX1276
* SX1278

---

# Communication Features

* CRC16
* Packet counter
* ACK
* Automatic retransmission
* Failsafe
* Telemetry

---

# Development Workflow

1. Design
2. Documentation
3. Implementation
4. Testing
5. Review
6. Release
