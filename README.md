# RoboKosonsoy Link (RKL)

> Open-source long-range radio communication library for Arduino, ESP32 and EBYTE E32 LoRa modules.

## Overview

RoboKosonsoy Link (RKL) is an open-source communication library designed for reliable and low-latency wireless control of robots, RC aircraft, autonomous vehicles, and educational robotics projects.

The library provides a high-level API for EBYTE E32 LoRa modules while hiding low-level configuration details. It is designed to be simple for beginners and flexible enough for advanced applications.

## Sprint 3 Architecture

The library is organized into three production-oriented layers:

* `core` - fixed configuration, result codes, shared types and CRC16-CCITT.
* `drivers` - radio abstraction plus the EBYTE E32-433T30D driver.
* `protocol` - packet model, serializer, parser, ACK handling, retry policy and reliable link API.

The code is written for Arduino C++17 without exceptions, dynamic allocation or `String`, keeping RAM usage small enough for Arduino Nano / ATmega328P.

## Packet Format

```text
start byte | packet type | sequence id | payload length | payload | crc16
```

CRC16 is calculated over `packet type`, `sequence id`, `payload length` and `payload`.

## Reliable Link

`RKL::Link` provides:

* `sendPacket()` with automatic sequence numbers, ACK wait and retry.
* `receivePacket()` with timeout, CRC verification, automatic ACK response and duplicate detection.
* Configurable retry count and ACK timeout through `RKL::RetryConfig`.

## Project Goals

* Reliable long-range communication
* Low latency for RC control
* Easy-to-use API
* Modular architecture
* Portable across Arduino and ESP32 platforms
* Comprehensive documentation
* Educational examples

## Planned Features

### Radio Driver

* Full E32 configuration
* Read/write module settings
* Automatic mode switching
* Channel management
* Power configuration
* Air data rate configuration

### Communication Protocol

* CRC16 error detection
* Packet validation
* Packet counter
* ACK support
* Automatic retransmission
* Failsafe
* Connection monitoring

### Telemetry

* RSSI
* Battery voltage
* Temperature
* Flight status
* Custom telemetry packets

### Supported Hardware

Current targets:

* Arduino Nano
* Arduino Uno
* ESP32
* EBYTE E32-433T30D

Future targets:

* SX1276
* SX1278
* Other LoRa transceivers

## Repository Structure

```text
docs/
examples/
  CRC16_Test/
  CRC_Test/
  E32_Test/
  Packet_Test/
hardware/
src/
  core/
  drivers/
  protocol/
tests/
```

## Project Status

Current version:

**v0.1 Alpha**

The project is under active development.

## Roadmap

* v0.1 - Project foundation
* v0.2 - E32 driver
* v0.3 - Communication protocol
* v0.4 - RC transmitter
* v0.5 - RC receiver
* v0.6 - Telemetry
* v1.0 вЂ” Stable release

## License

This project is released under the MIT License.

## Author

Created by the RoboKosonsoy community.

## Contributions

Contributions, bug reports, feature requests, and pull requests are welcome.
