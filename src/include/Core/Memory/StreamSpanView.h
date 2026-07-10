#pragma once

#include "Core/Memory/SpanReader.h"
#include "Core/Memory/SpanWriter.h"

namespace ml {

/**
 * A view of a length prefixed span of items in a memory stream
 * @tparam TLengthPrefix The type of the length prefix
 * @tparam T The type of element in the span
 */
template <typename TLengthPrefix, typename T>
class StreamSpanView {
public:
    StreamSpanView() = default;

    explicit StreamSpanView(const T* ptr, TLengthPrefix length) {
        mPtr = ptr;
        mLength = length;
    }

    void serialize(SpanWriter* writer) const {
        writer->write(mLength);
        writer->write(mPtr, this->byteCount());
    }

    void deserialize(SpanReader* reader) {
        mLength = reader->read<TLengthPrefix>();
        mPtr = reader->readView<const T>(mLength);
    }

    TLengthPrefix elemCount() const { return mLength / sizeof(T); }
    TLengthPrefix byteCount() const { return mLength * sizeof(T); }

    const T* begin() { return mPtr; }
    const T* end() { return mPtr + mLength; }

    const T* data() const { return mPtr; }
    operator const T*() const { return mPtr; }

    T operator[](TLengthPrefix i) { return mPtr[i]; }
    const T& operator[](TLengthPrefix i) const { return mPtr[i]; }

private:
    const T* mPtr = nullptr;
    TLengthPrefix mLength = 0;
};

}
