#ifndef RKL_CONFIG_H
#define RKL_CONFIG_H

/*
 * RoboKosonsoy Link (RKL)
 * Global configuration
 *
 * Copyright (c) RoboKosonsoy Community
 * Licensed under the MIT License
 */

#include <Arduino.h>

namespace RKL
{

//---------------------------------------------------------------------
// Protocol constants (реальный формат: 4 байта заголовка)
//---------------------------------------------------------------------

constexpr uint8_t PROTOCOL_VERSION = 1;       // не используется в пакете, зарезервировано
constexpr uint8_t START_BYTE       = 0xAA;
constexpr uint8_t PACKET_HEADER_SIZE = 4;     // start, type, id, length
constexpr uint8_t CRC_SIZE = 2;

//---------------------------------------------------------------------
// Packet limits
//---------------------------------------------------------------------

constexpr uint8_t MAX_PAYLOAD_SIZE = 48;
constexpr uint8_t MAX_PACKET_SIZE  = PACKET_HEADER_SIZE + MAX_PAYLOAD_SIZE + CRC_SIZE; // 4+48+2=54

//---------------------------------------------------------------------
// Timeouts (миллисекунды) – увеличены для надёжности LoRa
//---------------------------------------------------------------------

constexpr uint16_t ACK_TIMEOUT     = 500;    // было 100
constexpr uint16_t LINK_TIMEOUT    = 2000;   // было 1000
constexpr uint16_t AUX_TIMEOUT     = 500;

//---------------------------------------------------------------------
// Retry
//---------------------------------------------------------------------

constexpr uint8_t MAX_RETRY_COUNT = 3;

//---------------------------------------------------------------------
// Serial
//---------------------------------------------------------------------

constexpr uint32_t DEFAULT_BAUDRATE = 9600;

} // namespace RKL

#endif