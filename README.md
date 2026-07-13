# RoboKosonsoy Link (RKL)

> Open-source long-range radio communication library for Arduino, ESP32 and EBYTE E32 LoRa modules.

## Overview

RoboKosonsoy Link (RKL) is an open-source communication library designed for reliable and low-latency wireless control of robots, RC aircraft, autonomous vehicles, and educational robotics projects.

The library provides a high-level API for EBYTE E32 LoRa modules while hiding low-level configuration details. It is designed to be simple for beginners and flexible enough for advanced applications.

## Architecture

The library is organized into three layers:

* `core` – shared types, CRC16, configuration and error handling.
* `drivers` – radio abstraction and the EBYTE E32 driver.
* `protocol` – packet model, serializer, parser, ACK, retry logic and reliable link API.

The code is written for Arduino C++17 without exceptions, dynamic allocation or `String`, keeping RAM usage small enough for Arduino Nano / ATmega328P.

## Packet Format

```text
start byte | version | type | flags | counter (2 bytes) | length | payload | crc16