 #pragma once

namespace ml {

template <typename T>
class Diffable {
public:
    Diffable() : mCurrent() {

    }

    Diffable(const T& initial) {
        mCurrent = initial;
    }

    bool diff(const T& newValue) {
        bool isNew = newValue != mCurrent;
        mCurrent = newValue;
        return isNew;
    }

    T& current() { return mCurrent; }
    const T& current() const { return mCurrent; }

    operator T&() { return mCurrent; }
    operator const T&() const { return mCurrent; }

private:
    T mCurrent;
};

// TODO: Convert to DiffableString type
// template <>
// inline Diffable<const char*>::Diffable() {
//     mCurrent = ml::str::EmptyString;
// }
//
// template <>
// inline Diffable<const char*>::Diffable(const char* const& initial) {
//     if (initial != nullptr) {
//         mCurrent = initial;
//     } else {
//         mCurrent = ml::str::EmptyString;
//     }
// }
//
// template <>
// inline bool Diffable<const char*>::diff(const char* const& newValue) {
//     if (newValue == nullptr) {
//         mCurrent = ml::str::EmptyString;
//         return false;
//     }
//
//     bool isNew = std::strcmp(mCurrent, newValue) != 0;
//     mCurrent = newValue;
//     return isNew;
// }

}
