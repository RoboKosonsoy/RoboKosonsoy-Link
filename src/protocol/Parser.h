#ifndef RKL_PARSER_H
#define RKL_PARSER_H

#include <Arduino.h>
#include "../core/Result.h"
#include "Packet.h"

namespace RKL
{

class Parser
{
public:
    static Result parse(const uint8_t* buffer,
                        uint16_t size,
                        Packet& packet);
};

} // namespace RKL

#endif