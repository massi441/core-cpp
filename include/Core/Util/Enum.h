#pragma once

#include <cstdint>
#include <cstring>
#include "Core/Util/Recursion.h"

/**
 * A macro for generating an enum with metadata, and automatic string conversion utils
 * Note: This only works with enums that are sequential and starting from 0
 * You are not expected to manually assign values to each enum.
 * @param EnumName The name of the enum
 * @param BaseType The underlying type of the enum (short, int...)
 */
#define META_TYPED_ENUM(EnumName, BaseType, ...)                                                            \
    enum class EnumName : BaseType { EXPAND(FOR_EACH_RECURSE(IDENT, __VA_ARGS__)) };                        \
    constexpr const char* EnumName##_Strings[] = { EXPAND(FOR_EACH_RECURSE(STR, __VA_ARGS__)) };            \
                                                                                                            \
    constexpr const char* EnumName##_ToString(EnumName value) {                                             \
        return EnumName##_Strings[static_cast<int>(value)];                                                 \
    }                                                                                                       \
                                                                                                            \
    constexpr BaseType EnumName##_Count = sizeof(EnumName##_Strings) / sizeof(EnumName##_Strings[0]);       \
                                                                                                            \
    inline EnumName EnumName##_FromString(const char* name, EnumName defaultValue) {                        \
        for (BaseType i = 0; i < EnumName##_Count; i++) {                                                   \
            if (strcmp(EnumName##_ToString(static_cast<EnumName>(i)), name) == 0) {                         \
                return static_cast<EnumName>(i);                                                            \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return defaultValue;                                                                                \
    }                                                                                                       \
                                                                                                            \
    inline bool EnumName##_FromString(EnumName* outValue, const char* name) {                               \
        for (BaseType i = 0; i < EnumName##_Count; i++) {                                                   \
            if (strcmp(EnumName##_Strings[i], name) == 0) {                                                 \
                *outValue = static_cast<EnumName>(i);                                                       \
                return true;                                                                                \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return false;                                                                                       \
    }                                                                                                       \

#define META_ENUM(EnumName, ...) \
    META_TYPED_ENUM(EnumName, uint32_t, __VA_ARGS__)
