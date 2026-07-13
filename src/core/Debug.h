#pragma once

#include <Arduino.h>

#define RKL_DEBUG 1

#if RKL_DEBUG

#define RKL_LOG(x) Serial.print(x)
#define RKL_LOGLN(x) Serial.println(x)

void RKL_DebugHex(const uint8_t* data, uint16_t size);

#else

#define RKL_LOG(x)
#define RKL_LOGLN(x)

#endif