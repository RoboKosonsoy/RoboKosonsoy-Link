#ifndef RKL_ERROR_H
#define RKL_ERROR_H

#include <Arduino.h>
#include "Result.h"

namespace RKL
{

class Error
{
public:
    Error() : _result(Result::OK) {}
    explicit Error(Result result) : _result(result) {}

    Result code() const { return _result; }
    bool ok() const { return _result == Result::OK; }
    void clear() { _result = Result::OK; }
    void set(Result result) { _result = result; }

private:
    Result _result;
};

} // namespace RKL

#endif