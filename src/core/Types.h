#ifndef RKL_TYPES_H
#define RKL_TYPES_H

/*
 * RoboKosonsoy Link (RKL)
 * Common type definitions
 *
 * Copyright (c) RoboKosonsoy Community
 * Licensed under the MIT License
 */

#include <Arduino.h>

namespace RKL
{

/**
 * @file Types.h
 * @brief Common enums shared by drivers and protocol layers.
 */

// Supported radio modules
enum class RadioType : uint8_t
{
    E32 = 0
};

// Packet types
enum class PacketType : uint8_t
{
    RC_CONTROL   = 0x01,
    ACK          = 0x02,
    NACK         = 0x08,
    PING         = 0x03,
    TELEMETRY    = 0x04,
    CONFIG       = 0x05,
    HEARTBEAT    = 0x06,
    DEBUG        = 0x07
};

// Link state
enum class LinkState : uint8_t
{
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    FAILSAFE
};

} // namespace RKL

#endif // RKL_TYPES_H
