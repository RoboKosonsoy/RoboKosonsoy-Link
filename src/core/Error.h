#ifndef RKL_ERROR_H
#define RKL_ERROR_H

/**
 * @file Error.h
 * @brief Error information for RoboKosonsoy Link.
 */

#include <Arduino.h>
#include "Result.h"

namespace RKL
{

/**
 * @brief Stores information about the last operation error.
 */
class Error
{
public:

    Error()
        : _result(Result::OK)
    {
    }

    explicit Error(Result result)
        : _result(result)
    {
    }

    /**
     * @brief Returns the result code.
     */
    Result code() const
    {
        return _result;
    }

    /**
     * @brief Returns true if there is no error.
     */
    bool ok() const
    {
        return _result == Result::OK;
    }

    /**
     * @brief Clears the error state.
     */
    void clear()
    {
        _result = Result::OK;
    }

    /**
     * @brief Sets a new error code.
     */
    void set(Result result)
    {
        _result = result;
    }

private:

    Result _result;
};

} // namespace RKL

#endif // RKL_ERROR_H