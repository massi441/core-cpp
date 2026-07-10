#pragma once

#include "Core/Util/Types.h"
#include <cstring>
#include <cstdint>

namespace ml {

template <uint64_t Size>
class ByteBuffer {
public:
    ByteBuffer() = default;

    ByteBuffer& operator=(const ByteBuffer& other) {
        if (&other == this) {
            return *this;
        }

        std::memcpy(mBuf, other.mBuf, Size);
        return *this;
    }

    static uint64_t size() { return Size; }

    ml::byte* data() { return mBuf; }
    const ml::byte* cdata() const { return mBuf; }

private:
    ml::byte mBuf[Size] = {};
};

}
