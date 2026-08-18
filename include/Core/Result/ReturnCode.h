#pragma once

namespace ml {

// potential todo: use ml::String for the error message (to allow concatenated messages)

/**
 * A wrapper around a function's return code, with an optional status message.
 * Acts as an alternative to exceptions.
 */
class ReturnCode {
public:
    ReturnCode(int code) {
        mCode = code;
    }

    ReturnCode(bool isSuccess) {
        mCode = !isSuccess; // 0 (false) = success
        mMessage = "";
    }

    ReturnCode(const char* message, int code = 1) {
        mCode = code;
        mMessage = message;
    }

    static const ReturnCode Success;

    const char* message() const {
        return mMessage;
    }

    int code() const {
        return mCode;
    }

    bool isSuccess() const {
        return mCode == 0;
    }

    operator bool() const {
        return mCode == 0;
    }

    operator int() const {
        return mCode;
    }

    bool operator==(const ReturnCode& other) const {
        return mCode == other.mCode;
    }

    bool operator==(int code) const {
        return mCode == code;
    }

private:
    int mCode = 0;
    const char* mMessage = "";
};

inline const ReturnCode ReturnCode::Success = ReturnCode(0);

}
