#pragma once

#include "Core/Container/Array.h"

namespace ml {

/**
 * A container for a circular array
 * @tparam T The type of element in the array
 */
template <typename T>
class RingArray {
public:
    explicit RingArray() = default;

    explicit RingArray(uint64_t size) {
        mCurrent = 0;
        mArray = ml::Array<T>(size);
    }

    T& next() {
        if (++mCurrent > mArray.lastIdx()) {
            mCurrent = 0;
        }

        return mArray[mCurrent];
    }

    T& previous() {
        if (--mCurrent < 0) {
            mCurrent = mArray.lastIdx();
        }

        return mArray[mCurrent];
    }

    const T& peekNext() const {
        if (mCurrent == mArray.lastIdx()) {
            return mArray[0];
        }

        return mArray[mCurrent + 1];
    }

    const T& peekPrevious() const {
        if (mCurrent == 0) {
            return mArray.lastIdx();
        }

        return mArray[mCurrent - 1];
    }

    T& current() { return mArray[mCurrent]; }
    T& first() { return mArray.first(); }
    T& last() { return mArray.last(); }

    uint64_t size() const { return mArray.size(); }

    T* begin() { return mArray.begin(); }
    T* end() { return mArray.end(); }

    const T* cbegin() const { return mArray.cbegin(); }
    const T* cend() const { return mArray.cend(); }

    T& operator[](uint64_t idx) { return mArray[idx]; }
    const T& operator[](uint64_t idx) const { return mArray[idx]; }

private:
    ml::Array<T> mArray;
    uint64_t mCurrent;
};

}
