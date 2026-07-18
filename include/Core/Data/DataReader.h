#pragma once

#include <cstddef>

#include "Core/Util/Types.h"

namespace ml {

template <typename T>
class DataReaderArray;

/**
 * A source of data for named values
 * @tparam T The derived type of DataReader, to allow nested read sources
 */
template <typename T>
class DataReader {
public:
    DataReader() = default;

    virtual bool isValid() const = 0;

    virtual int readInt32(const char* entryName) const = 0;
    virtual uint readUInt32(const char* entryName) const = 0;
    virtual float readFloat(const char* entryName) const = 0;
    virtual double readDouble(const char* entryName) const = 0;
    virtual const char* readString(const char* entryName) const = 0;

    virtual T getSubReader(const char* entryName) const = 0;

    virtual DataReaderArray<T> toArray() const = 0;
    virtual DataReaderArray<T> toArray(const char* entryName) const = 0;

    virtual ~DataReader() = default;
};

/**
 * An array read from a DataReader, where each element in the array can be iterated as a DataReader
 * @tparam T The type of DataReader
 */
template <typename T>
class DataReaderArray {
public:
    explicit DataReaderArray(T::ArrayKind array) {
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
