#pragma once

#include "Core/Util/Types.h"

namespace ml {

template <typename T>
class DataWriteSourceArray;

template <typename T>
class DataWriteSource {
public:
    DataWriteSource() = default;

    virtual void writeInt32(const char* entryName, int value) = 0;
    virtual void writeUInt32(const char* entryName, uint value) = 0;
    virtual void writeFloat(const char* entryName, float value) = 0;
    virtual void writeDouble(const char* entryName, double value) = 0;
    virtual void writeString(const char* entryName, const char* string) = 0;

    virtual T getInner(const char* entryName) const = 0;

    virtual DataWriteSourceArray<T> toArray() const = 0;
    virtual DataWriteSourceArray<T> toArray(const char* entryName) = 0;

    virtual bool flush() = 0;

    virtual ~DataWriteSource() = default;
};

template <typename T>
class DataWriteSourceArray {
public:
    explicit DataWriteSourceArray(T::ArrayKind array) {
        mArray = array;
    }

    T add() {
        return T(mArray.template add<typename T::ArrayNodeKind>());
    }

private:
    T::ArrayKind mArray;
};

}
