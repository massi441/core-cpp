#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <sstream>

namespace ml {

inline constexpr const char* EmptyString = "";

inline bool streql(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}

inline char intAsChar(int num) {
    return static_cast<char>('0' + num);
}

/**
 * Copies and null terminates a string up to an exclusive delimiter character.
 * If no delimiter is found, the entire source string is copied into the destination
 * @param dest The destination string
 * @param source The source string
 * @param delimiter The exclusive delimiter character
 */
inline void strdcpy(char* dest, const char* source, char delimiter) {
    while (*source != delimiter && *source != '\0') {
        *dest++ = *source++;
    }

    *dest = '\0';
}

inline int delimiterOffset(const char* source, char delimiter) {
    const char* delimPtr = std::strchr(source, delimiter);

    if (delimPtr == nullptr) {
        return -1;
    }

    return delimPtr - source;
}

inline std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> symbols;
    std::stringstream stream = std::stringstream(str);
    std::string buffer;

    while (std::getline(stream, buffer, delimiter)) {
        symbols.push_back(buffer);
    }

    return symbols;
}

// TODO: Add case insensitive comparison

// inline bool endsWith(const char* source, char end) {
//     return false;
// }

}
