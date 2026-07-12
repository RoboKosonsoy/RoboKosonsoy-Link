#ifndef RKL_E32_CONFIG_H
#define RKL_E32_CONFIG_H

#include <Arduino.h>

namespace RKL
{

struct E32Config
{
    uint8_t addh = 0x00;
    uint8_t addl = 0x00;
    uint8_t sped = 0x1A;   // 9600bps, 8N1
    uint8_t chan = 0x17;   // канал 23 (433.23 МГц)
    uint8_t option = 0x44; // фиксированная длина, без FEC

    void setDefault()
    {
        addh = 0x00;
        addl = 0x00;
        sped = 0x1A;
        chan = 0x17;
        option = 0x44;
    }
};

} // namespace RKL

#endif