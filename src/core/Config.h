#ifndef RKL_CONFIG_H
#define RKL_CONFIG_H

#include <Arduino.h>

namespace RKL
{

constexpr uint8_t PROTOCOL_VERSION = 1;
constexpr uint8_t START_BYTE = 0xAA;
constexpr uint8_t PACKET_HEADER_SIZE = 7;
constexpr uint8_t CRC_SIZE = 2;
constexpr uint8_t MAX_PAYLOAD_SIZE = 48;
constexpr uint8_t MAX_PACKET_SIZE = PACKET_HEADER_SIZE + MAX_PAYLOAD_SIZE + CRC_SIZE; // 57

constexpr uint16_t ACK_TIMEOUT = 500;
constexpr uint16_t LINK_TIMEOUT = 2000;
constexpr uint16_t AUX_TIMEOUT = 500;

constexpr uint8_t MAX_RETRY_COUNT = 3;
constexpr uint32_t DEFAULT_BAUDRATE = 9600;

} // namespace RKL

#endif