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
// Protocol
//---------------------------------------------------------------------

constexpr uint8_t PROTOCOL_VERSION = 1;
constexpr uint8_t START_BYTE       = 0xAA;

//---------------------------------------------------------------------
// Packet
//---------------------------------------------------------------------

constexpr uint8_t MAX_PAYLOAD_SIZE = 48;
constexpr uint8_t MAX_PACKET_SIZE  = 64;

//---------------------------------------------------------------------
// Timeouts (milliseconds)
//---------------------------------------------------------------------

constexpr uint16_t ACK_TIMEOUT     = 100;
constexpr uint16_t LINK_TIMEOUT    = 1000;
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

#endif // RKL_CONFIG_H