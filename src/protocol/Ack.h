#ifndef RKL_ACK_H
#define RKL_ACK_H

#include <Arduino.h>
#include "../core/Types.h"
#include "Packet.h"

namespace RKL
{

class Ack
{
public:
    Ack();
    void reset();
    bool isAckFor(const Packet& ackPacket, uint16_t counter) const;
    bool isDuplicate(const Packet& packet);
    static void make(Packet& packet, uint16_t counter);

private:
    bool _hasLastCounter;
    uint16_t _lastCounter;
};

} // namespace RKL

#endif