#include "Debug.h"

#if RKL_DEBUG

void RKL_DebugHex(const uint8_t* data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        if (data[i] < 16)
            Serial.print('0');

        Serial.print(data[i], HEX);
        Serial.print(' ');
    }

    Serial.println();
}

#endif