#pragma once

#include <string>

namespace ml {

inline uint32_t toUInt32(const std::string& str, uint32_t fallback) {
    try {
        return std::stoi(str);
    } catch (...) {
        return fallback;
    }
}

inline int64_t toInt64(const std::string& str, int64_t fallback) {
    try {
        return std::stoll(str);
    } catch (...) {
        return fallback;
    }
}

}
