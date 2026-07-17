#pragma once

#include "Core/Container/Array.h"
#include "Core/Util/Macros.h"

namespace ml {

template <typename T>
class PointerArray final : public ml::Container<PointerArray<T>, T*> {
    NO_COPY(PointerArray)
public:
    explicit PointerArray() = default;

    explicit PointerArray(uint64_t size) {
        mArray = ml::Array<T*>(size);
    }

    explicit PointerArray(std::vector<T*>&& vector) : mArray(std::move(vector)) {

    }

    PointerArray(PointerArray&& other) noexcept {
        mArray = std::move(other.mArray);
    }

    PointerArray& operator=(PointerArray&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        mArray = std::move(other.mArray);

        return *this;
    }

    void set(uint64_t index, T* ptr) {
        delete mArray[index];
        mArray[index] = ptr;
    }

    bool replace(T* oldPtr, T* newPtr) {
        if (oldPtr == newPtr) {
            return true;
        }

        for (T*& ptr : mArray) {
            if (ptr == oldPtr) {
                delete oldPtr;
                ptr = newPtr;
                return true;
            }
        }

        return false;
    }

    void remove(uint64_t index) {
        delete mArray[index];
        mArray[index] = nullptr;
    }

    bool remove(T* item) {
        for (T*& ptr : mArray) {
            if (ptr == item) {
                delete ptr;
                ptr = nullptr;
                return true;
            }
        }

        return false;
    }

    ~PointerArray() {
        for (T* ptr : mArray) {
            delete ptr;
        }
    }

    T** begin() { return mArray.begin(); }
    T** end() { return mArray.end(); }
    T* const* begin() const { return mArray.begin(); }
    T* const* end() const { return mArray.end(); }

    uint64_t size() const { return mArray.size(); }

    T* operator[](uint64_t index) { return mArray[index]; }
    const T* operator[](uint64_t index) const { return mArray[index]; }

private:
    ml::Array<T*> mArray;
};

}
