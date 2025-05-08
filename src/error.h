#pragma once

#include <stdexcept>
#include <string>

enum class ErrorCode { IndexOutOfRange, NullPointer };

class ErrorInfo : public std::runtime_error {
public:
    ErrorInfo(ErrorCode code, const std::string& msg) : code(code), std::runtime_error(msg) {
    }

    ErrorCode Code() const {
        return code;
    }

private:
    ErrorCode code;
};
