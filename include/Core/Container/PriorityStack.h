#pragma once

#include "Core/Container/Array.h"
#include "Core/Util/MathHelpers.h"

namespace ml {

/**
 * A fixed-size container where the most recently pushed element is always at the front.
 * Unlike a traditional stack, any element at any position can be popped, as items get
 * shifted back to preserve item order.
 * @tparam T The type of item stored in the stack
 */
template <std::default_initializable T>
class PriorityStack {
public:
    explicit PriorityStack() : mStack() {

    }

    /**
     * Constructs a PriorityStack with the size provided, if it is greater or equal than 1
     * @param size The size of the stack
     */
    explicit PriorityStack(uint64_t size) : mStack(mathi::max(1, size)) {

    }

    /**
     * Pushes an element at the front of the stack, and shifts all other
     * elements forward by one slot.
     * @param item The item to push on the stack
     */
    void push(const T& item) {
        T* it = mStack.end() - 1;
        T* front = mStack.begin();

        while (it != front) {
            *it = *(it - 1);

            --it;
        }

        mStack[0] = item;
    }

    /**
     * Pushes an element on the stack if it isn't already present
     * @param item The item to push on the stack
     */
    void pushUnique(const T& item) {
        if (mStack.contains(item)) {
            return;
        }

        this->push(item);
    }

    /**
     * Pops an element out of the PriorityStack, and shifts back all elements
     * after the removed element back by one slot.
     * @param item The item to remove
     */
    void pop(const T& item) {
        T* it = mStack.begin();
        T* back = mStack.end() - 1;

        bool isTargetFound = false;

        while (it != back) {
            if (*it == item) {
                isTargetFound = true;
            }

            if (isTargetFound) {
                *it = *(it + 1);
            }

            ++it;
        }

        if (isTargetFound) {
            *back = T();
        }
    }

    const T& active() {
        return mStack[0];
    }

    const ml::Array<T>& stack() const {
        return mStack;
    }

private:
    ml::Array<T> mStack;
};

}
