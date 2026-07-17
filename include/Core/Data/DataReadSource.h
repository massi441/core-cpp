#pragma once

#include "Core/Util/Types.h"

#include <cstdint>
#include <cstddef>

namespace ml {

template <typename T>
class DataReadSourceArray;

template <typename T>
class DataReadSource {
public:
    DataReadSource() = default;

    virtual bool isValid() const = 0;

    virtual uint readUInt32(const char* entryName) const = 0;
    virtual int readInt32(const char* entryName) const = 0;
    virtual float readFloat(const char* entryName) const = 0;
    virtual double readDouble(const char* entryName) const = 0;
    virtual const char* readString(const char* entryName) const = 0;

    virtual T readInner(const char* entryName) const = 0;

    virtual DataReadSourceArray<T> toArray() const = 0;
    virtual DataReadSourceArray<T> toArray(const char* entryName) const = 0;

    virtual ~DataReadSource() = default;
};

template <typename T>
class DataReadSourceArray {
public:
    DataReadSourceArray(T::ArrayKind array) {
        mArray = array;
    }

    class Iterator {
    public:
        explicit Iterator(T::IteratorKind iterator) {
            mCurrent = iterator;
        }

        Iterator& operator++() {
            ++mCurrent;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return mCurrent != other.mCurrent;
        }

        T operator*() const {
            return T(*mCurrent);
        }

    private:
        T::IteratorKind mCurrent;
    };

    Iterator begin() const { return Iterator(mArray.begin()); }
    Iterator end() const { return Iterator(mArray.end()); }

    size_t size() const { return mArray.size(); }

private:
    T::ArrayKind mArray;
};

}
