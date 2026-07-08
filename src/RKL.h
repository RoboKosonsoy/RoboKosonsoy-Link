#ifndef RKL_H
#define RKL_H

/*
 * RoboKosonsoy Link (RKL)
 * Main library header
 *
 * Copyright (c) RoboKosonsoy Community
 * Licensed under the MIT License
 */

#include <Arduino.h>

// Core
#include "core/Types.h"
#include "core/Config.h"
#include "core/Result.h"
#include "core/CRC16.h"

// Drivers
#include "drivers/Radio.h"
#include "drivers/E32.h"

// Protocol
#include "protocol/Link.h"

#endif // RKL_H