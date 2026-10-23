#pragma once

#include <cstdint>
#include <type_traits>

namespace ml {

/**
 * A utility wrapper around a bit set.
 * The flag methods take enum values that are bit masks (1 << n),
 * the index methods take enum values that are bit indices (0, 1, 2...), such as DATA_ENUM values.
 * @tparam T The underlying type of the bit set (int32, int64...)
 * @tparam F The different flags values for the bit set.
 */
template <typename T, typename F>
requires std::is_integral_v<T> && std::is_enum_v<F>
class BitSet {
public:
    void enable(F flag) {
        mFlags |= static_cast<T>(flag);
    }

    void disable(F flag) {
        mFlags &= ~static_cast<T>(flag);
    }

    void enableIndex(F index) {
        mFlags |= IndexMask(index);
    }

    void disableIndex(F index) {
        mFlags &= ~IndexMask(index);
    }

    bool isIndexEnabled(F index) const {
        return (mFlags & IndexMask(index)) != 0;
    }

    void enableAll() {
        mFlags = ~T(0);
    }

    void disableAll() {
        mFlags = 0;
    }

    bool isEnabled(F flag) const {
        return (mFlags & static_cast<T>(flag)) != 0;
    }

    bool isEmpty() const {
        return mFlags == 0;
    }

    bool hasFlags() const {
        return mFlags != 0;
    }

    T getFlags() const {
        return mFlags;
    }

private:
    T mFlags = 0;

    static constexpr T IndexMask(F index) {
        return T(1) << static_cast<T>(index);
    }
};

template <typename F>
using UInt32BitSet = BitSet<uint32_t, F>;

template <typename T, typename F>
using ConfigFlags = BitSet<T, F>;

template <typename F>
using UInt32ConfigFlags = UInt32BitSet<F>;

}
