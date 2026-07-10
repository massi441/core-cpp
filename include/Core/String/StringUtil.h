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

inline std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> symbols;
    std::stringstream stream = std::stringstream(str);
    std::string buffer;

    while (std::getline(stream, buffer, delimiter)) {
        symbols.push_back(buffer);
    }

    return symbols;
}

// inline bool endsWith(const char* source, char end) {
//     return false;
// }

}
