#ifndef RKL_SERIALIZER_H
#define RKL_SERIALIZER_H

#include <Arduino.h>

#include "../core/Config.h"
#include "../core/Result.h"
#include "Packet.h"

namespace RKL
{

/**
 * @brief Converts Packet objects into the wire format.
 */
class Serializer
{
public:
    static Result serialize(Packet& packet,
                            uint8_t* buffer,
                            uint16_t bufferSize,
                            uint16_t& written);
};

} // namespace RKL

#endif // RKL_SERIALIZER_H
