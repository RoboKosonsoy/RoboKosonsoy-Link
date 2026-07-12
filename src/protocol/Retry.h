#ifndef RKL_RETRY_H
#define RKL_RETRY_H

#include <Arduino.h>
#include "../core/Config.h"

namespace RKL
{

struct RetryConfig
{
    uint8_t count = MAX_RETRY_COUNT;
    uint16_t timeout = ACK_TIMEOUT;
};

class Retry
{
public:
    explicit Retry(const RetryConfig& config = RetryConfig());

    void configure(const RetryConfig& config);
    void reset();
    bool canAttempt() const;
    void recordAttempt();
    uint8_t attempts() const;
    uint16_t timeout() const;

private:
    RetryConfig _config;
    uint8_t _attempts;
};

} // namespace RKL

#endif