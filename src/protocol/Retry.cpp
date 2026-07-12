#include "Retry.h"

namespace RKL
{

Retry::Retry(const RetryConfig& config)
    : _config(config), _attempts(0) {}

void Retry::configure(const RetryConfig& config)
{
    _config = config;
    reset();
}

void Retry::reset()
{
    _attempts = 0;
}

bool Retry::canAttempt() const
{
    return _attempts <= _config.count;
}

void Retry::recordAttempt()
{
    if (_attempts < 255)
        _attempts++;
}

uint8_t Retry::attempts() const
{
    return _attempts;
}

uint16_t Retry::timeout() const
{
    return _config.timeout;
}

} // namespace RKL