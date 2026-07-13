#ifndef RKL_LINK_H
#define RKL_LINK_H

#include <Arduino.h>
#include "../core/Config.h"
#include "../core/Result.h"
#include "../drivers/Radio.h"
#include "Ack.h"
#include "Packet.h"
#include "Retry.h"

namespace RKL
{

class Link
{
public:
    explicit Link(Radio& radio);

    void setRetryConfig(const RetryConfig& config);
    uint16_t nextCounter();

    Result sendPacket(Packet& packet);
    Result receivePacket(Packet& packet, uint16_t timeout = LINK_TIMEOUT, bool sendAck = true);

    Result send(Packet& packet);
    Result receive(Packet& packet);

private:
    Result sendOnce(Packet& packet);
    Result waitForAck(uint16_t counter, uint16_t timeout);
    Result readByte(uint8_t& value, uint32_t deadline);
    Result readFrame(uint16_t& frameSize, uint16_t timeout);

    Radio& _radio;
    Ack _ack;
    Retry _retry;
    uint16_t _nextCounter;
    uint8_t _buffer[MAX_PACKET_SIZE];
};

} // namespace RKL

#endif