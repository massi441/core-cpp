#pragma once

#include "Core/Container/Array.h"
#include <utility>

namespace ml {

template <typename T>
class ArrayQueue {
public:
    ArrayQueue() = default;

    explicit ArrayQueue(uint64_t size) {
        mArray = ml::Array<T>(size);
        mCount = 0;
    }
    
    bool pop(T* outItem) {
        if (this->isEmpty()) {
            return false;
        }

        *outItem = std::move(mArray[mHead]);

        if (++mHead >= mArray.size()) {
            mHead = 0;
        }

        mCount--;

        return true;
    }

    template <typename F>
    bool push(F&& item) {
        if (this->isFull()) {
            return false;            
        }

        uint64_t index = mHead + mCount;
        if (index >= mArray.size()) {
            index -= mArray.size();
        }

        mCount++;
        mArray[index] = std::forward<F>(item);

        return true;
    }

    void reset() {
        mHead = 0;
        mCount = 0;
    }

    bool isEmpty() const {
        return mCount == 0;
    }

    bool isFull() const {
        return mCount == mArray.size();
    }
    
    uint64_t size() const {
        return mCount;
    }
    
    uint64_t capacity() const {
        return mArray.size();
    }

private:
    ml::Array<T> mArray;
    uint64_t mHead = 0;
    uint64_t mCount = 0;
};

}
