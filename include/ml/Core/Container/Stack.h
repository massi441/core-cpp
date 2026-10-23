#pragma once

#include <array>

namespace ml {

/**
 * A fixed-size, stack allocated stack for pushing and popping elements onto it
 * @tparam T The type of element stored in the stack
 * @tparam Size The size of the stack
 */
template <typename T, size_t Size>
class Stack final {
public:
    Stack() {
        mTop = mBuf.begin() - 1;
    }

    template <typename F>
    bool push(F&& item) {
        if (this->isFull()) {
            return false;
        }

        mTop++;
        *mTop = std::forward<F>(item);

        return true;
    }

    bool pop(T* outItem) {
        if (this->isEmpty()) {
            return false;
        }

        *outItem = *mTop;
        mTop--;

        return true;
    }

    bool isFull() const { return mTop == mBuf.end() - 1; }
    bool isEmpty() const { return mTop == mBuf.begin() - 1; }

private:
    std::array<T, Size> mBuf;
    T* mTop = mBuf.begin() - 1;
};

}
