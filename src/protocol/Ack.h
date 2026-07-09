#ifndef RKL_ACK_H
#define RKL_ACK_H

#include <Arduino.h>

#include "../core/Types.h"
#include "Packet.h"

namespace RKL
{

/**
 * @brief ACK helpers and duplicate sequence detection.
 */
class Ack
{
public:
    Ack();

    void reset();
    bool isAckFor(const Packet& ackPacket, uint8_t sequence) const;
    bool isDuplicate(const Packet& packet);
    static void make(Packet& packet, uint8_t sequence);

private:
    bool _hasLastSequence;
    uint8_t _lastSequence;
};

} // namespace RKL

#endif // RKL_ACK_H
