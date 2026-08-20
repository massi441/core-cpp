#pragma once

#include <string>

#include "Core/String/StringUtil.h"

namespace ml {

/**
 * A wrapper around a function's success status, with an optional error message for failures.
 * Acts as an alternative to exceptions.
 */
class ReturnStatus {
public:
    ReturnStatus(bool isSuccess) {
        mIsSuccess = isSuccess;
        mMessage = "";
    }

    ReturnStatus(const std::string& message) {
        mIsSuccess = false;
        mMessage = message;
    }

    template <typename ...Args>
    requires (std::same_as<Args, const char*>&& ...)
    explicit ReturnStatus(Args... strings) {
        mIsSuccess = false;
        mMessage = ml::concatString(strings...);
    }

    explicit ReturnStatus(std::error_code ec) {
        mIsSuccess = !ec;
        mMessage = mIsSuccess ? "" : ec.message();
    }

    bool isSuccess() const {
        return mIsSuccess;
    }

    const char* message() const {
        return mMessage.c_str();
    }

    operator bool() const {
        return mIsSuccess;
    }

private:
    bool mIsSuccess;
    std::string mMessage;
};

}
