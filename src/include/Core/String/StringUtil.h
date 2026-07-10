#pragma once

#include <cstring>

namespace ml {

inline constexpr const char* EmptyString = "";

inline void strdcpy(char* dest, const char* source, char delimiter) {
    const char* nextDelim = source - 1;
    while (*++nextDelim != delimiter && (*dest++ = *source++) != '\0');
    *dest = '\0';
}

inline int delimiterOffset(const char* source, char delimiter) {
    const char* delimPtr = std::strchr(source, delimiter);

    if (delimPtr == nullptr) {
        return -1;
    }

    return delimPtr - source;
}

// inline bool endsWith(const char* source, char end) {
//     return false;
// }

}
