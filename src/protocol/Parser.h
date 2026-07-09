#ifndef RKL_PARSER_H
#define RKL_PARSER_H

#include <Arduino.h>

#include "../core/Result.h"
#include "Packet.h"

namespace RKL
{

/**
 * @brief Parses and validates the RKL wire packet format.
 */
class Parser
{
public:
    static Result parse(const uint8_t* buffer,
                        uint16_t size,
                        Packet& packet);
};

} // namespace RKL

#endif // RKL_PARSER_H
