#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace ml {

/**
 * A container for a dynamically allocated, but fixed-size C-style array.
 */
template <typename T>
class Array {
public:
    static const Array Empty;

    /**
     * Constructs an uninitialized Array. To use only when allocation
     * needs to be deferred from object creation.
     *
     * Using an uninitialized Array is UB.
     */
    explicit Array() {
        mBuffer = nullptr;
        mSize = 0;
    }

    /**
     * Constructs a Array with the size provided.
     * @param size The size of the array
     */
    explicit Array(uint64_t size) {
        mBuffer = new T[size]();
        mSize = size;
    }

    explicit Array(const std::vector<T>& vector) : Array(vector.size()) {
        for (uint64_t i = 0; i < vector.size(); i++) {
            mBuffer[i] = vector[i];
        }
    }

    explicit Array(std::vector<T>&& vector) : Array(vector.size()) {
        for (uint64_t i = 0; i < vector.size(); i++) {
            mBuffer[i] = std::move(vector[i]);
        }
    }

    Array(const Array& other) {
        this->copy(other);
    }

    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }

        delete[] mBuffer;

        this->copy(other);

        return *this;
    }

    Array(Array&& other) noexcept {
        this->steal(std::move(other));
    }

    Array& operator=(Array&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] mBuffer;

        this->steal(std::move(other));

        return *this;
    }

    ~Array() {
        delete[] mBuffer;
    }

    T* safeAt(uint64_t index) {
        if (!this->isInBounds(index)) {
            return nullptr;
        }

        return &mBuffer[index];
    }

    bool isInBounds(uint64_t idx) const {
        return idx < mSize;
    }

    T* find(const T& item) {
        for (T& it : *this) {
            if (it == item) {
                return &it;
            }
        }

        return nullptr;
    }

    template <typename F>
    T* findIf(const F& predicate) {
        for (T& it : *this) {
            if (predicate(it)) {
                return &it;
            }
        }

        return nullptr;
    }

    const T* find(const T& item) const {
        for (const T& it : *this) {
            if (it == item) {
                return &it;
            }
        }

        return nullptr;
    }

    template <typename F>
    const T* findIf(const F& predicate) const {
        for (const T& it : *this) {
            if (predicate(it)) {
                return &it;
            }
        }

        return nullptr;
    }

    template <typename B>
    requires std::is_convertible_v<T, B>
    bool contains(const B& item) const {
        for (const T& it : *this) {
            if (it == item) {
                return true;
            }
        }

        return false;
    }

    /**
     * Checks if an item is contained within the array using == comparison
     * @param item The item to check for
     * @return true if the item is inside the array, false otherwise
     */
    bool contains(const T& item) const {
        return this->contains<T>(item);
    }

    template <typename F>
    bool containsIf(const F& predicate) const {
        for (const T& item : *this) {
            if (predicate(item)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Computes the index of an item within the array, using == comparison
     * @param item The item to compute the index of
     * @return The index of the item if it is found, UINT64_MAX otherwise
     */
    uint64_t indexOf(const T& item) const {
        const T* it = this->begin();
        const T* end = this->end();

        while (it != end) {
            if (*it == item) {
                return it - this->begin();
            }

            ++it;
        }

        return UINT64_MAX;
    }

    /**
     * Replaces the first occurrence of the target item with the provided value
     * @param target The target item to replace
     * @param value The value to replace the target with
     * @return True if the target was replaced, false otherwise
     */
    bool replaceFirst(const T& target, const T& value) {
        for (T& item : *this) {
            if (item == target) {
                item = value;
                return true;
            }
        }

        return false;
    }

    /**
     * Swaps two elements in the array at the provided indices.
     * Note: The objects are copied during the swap, and no index validation is performed
     * @param idx1 The index of the first element to swap
     * @param idx2 The index of the second element to swap
     */
    void swap(uint64_t idx1, uint64_t idx2) {
        T x = std::move(mBuffer[idx1]);

        mBuffer[idx1] = std::move(mBuffer[idx2]);
        mBuffer[idx2] = std::move(x);
    }

    uint64_t maxIndex() const {
        return mSize - 1;
    }

    T* data() { return mBuffer; }
    const T* cdata() const { return mBuffer; }
    uint64_t size() const { return mSize; }
    uint64_t beginIdx() const { return 0; }
    uint64_t endIdx() const { return mSize; }
    uint64_t lastIdx() const { return mSize - 1; }

    T* begin() { return mBuffer; }
    T* end() { return mBuffer + mSize; }
    const T* begin() const { return mBuffer; }
    const T* end() const { return mBuffer + mSize; }

    T& first() { return mBuffer[0]; }
    const T& first() const { return mBuffer[0]; }
    T& last() { return mBuffer[mSize - 1]; }
    const T& last() const { return mBuffer[mSize - 1]; }

    T& operator[](uint64_t i) { return mBuffer[i]; }
    const T& operator[](uint64_t i) const { return mBuffer[i]; }

    explicit operator const T*() const { return mBuffer; }
    explicit operator T*() const { return mBuffer; }

private:
    T* mBuffer;
    uint64_t mSize;

    void copy(const Array& other) {
        mSize = other.mSize;
        mBuffer = nullptr;

        if (mSize > 0) {
            mBuffer = new T[mSize];

            for (uint64_t i = 0; i < mSize; i++) {
                mBuffer[i] = other.mBuffer[i];
            }
        }
    }

    void steal(Array&& other) {
        mBuffer = other.mBuffer;
        mSize = other.mSize;

        other.mBuffer = nullptr;
        other.mSize = 0;
    }
};

template <typename T>
const Array<T> Array<T>::Empty = Array(0);

template <>
inline bool Array<const char*>::contains(const char* const& item) const {
    for (const char* str : *this) {
        if (str == item || strcmp(str, item) == 0) {
            return true;
        }
    }

    return false;
}

}
