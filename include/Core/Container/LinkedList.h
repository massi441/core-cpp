#pragma once

#include <cstdint>

namespace ml {

// TODO: Implement

template <typename T>
class LinkedListNode {
    T value;
    LinkedListNode* prev = nullptr;
    LinkedListNode* next = nullptr;
};

template <typename T>
class LinkedList {
public:
    LinkedList() = default;

private:
    LinkedListNode<T>* mHead = nullptr;
    LinkedListNode<T>* mTail = nullptr;
    uint64_t mCount = 0;
};

}
