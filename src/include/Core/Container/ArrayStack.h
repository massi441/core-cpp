#pragma once

#include "Core/Container/Array.h"

namespace ml {

/**
 * A fixed size stack backed by an Array
 * @tparam T The type of element stored on the stack
 */
template <typename T>
class ArrayStack {
public:
    ArrayStack() = default;

    explicit ArrayStack(uint64_t size) {
        mArray = ml::Array<T>(size);
        mTop = mArray.begin() - 1;
    }

    template <typename F>
    bool push(F&& item) {
        if (this->isFull()) {
            return false;
        }

        ++mTop;
        *mTop = std::forward<F>(item);

        return true;
    }

    bool pop(T* outItem) {
        if (this->isEmpty()) {
            return false;
        }

        *outItem = std::move(*mTop);
        --mTop;

        return true;
    }

    bool isFull() const { return mTop == mArray.end() - 1; }
    bool isEmpty() const { return mTop == mArray.begin() - 1; }

private:
    ml::Array<T> mArray;
    T* mTop = nullptr;
};

}
