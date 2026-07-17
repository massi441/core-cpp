#pragma once

#include <memory>

#include "Core/Container/Array.h"
#include "Core/Util/Macros.h"

namespace ml {

/**
 * A container for an array of owned pointers
 * @tparam T The type of object pointed to
 */
template <typename T>
requires (!std::is_pointer_v<T>)
class PointerArray final : public ml::Container<PointerArray<T>, T*> {
    NO_COPY(PointerArray)
public:
    static constexpr uint64_t InvalidIndex = ml::Array<T>::InvalidIndex;

    explicit PointerArray() = default;

    explicit PointerArray(uint64_t size) {
        mArray = ml::Array<T*>(size);
    }

    explicit PointerArray(std::vector<T*>&& vector) : mArray(std::move(vector)) {

    }

    PointerArray(std::initializer_list<T> list) : mArray(list) {

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

    template <typename ...Args>
    void emplace(uint64_t index, Args&&... args) {
        delete mArray[index];
        mArray[index] = new T(std::forward<Args>(args)...);
    }

    void emplaceNew(uint64_t index) requires (std::is_default_constructible_v<T>) {
        this->set(index, new T());
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

    std::unique_ptr<T> release(uint64_t index) {
        T* item = mArray[index];
        mArray[index] = nullptr;
        return std::unique_ptr<T>(item);
    }

    std::unique_ptr<T> release(T* item) {
        for (T*& ptr : mArray) {
            if (ptr == item) {
                ptr = nullptr;
                return std::unique_ptr<T>(item);
            }
        }

        return nullptr;
    }

    ~PointerArray() {
        for (T* ptr : mArray) {
            delete ptr;
        }
    }

    bool isInBounds(uint64_t index) const {
        return mArray.isInBounds(index);
    }

    T* safeAt(uint64_t index) {
        if (index >= mArray.size()) {
            return nullptr;
        }

        return mArray[index];
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
