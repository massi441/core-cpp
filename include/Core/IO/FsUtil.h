#pragma once

#include <filesystem>

namespace ml {

template <typename ... Args>
std::filesystem::path fromCurrentPath(Args... args) {
    std::filesystem::path result = std::filesystem::current_path();
    (result.append(std::forward<Args>(args)), ...);
    return result;
}

template <typename ...Args>
std::filesystem::path makePath(Args&& ...args) {
    std::filesystem::path result;
    (result.append(std::forward<Args>(args)), ...);
    return result;
}

bool ensureDirCreated(const std::filesystem::path& path);
bool clearDirectory(const std::filesystem::path& path);
bool removeDirectory(const std::filesystem::path& path);
bool isExistPath(const std::filesystem::path& path);
bool isExistParentPath(const std::filesystem::path& path);
bool createDirectory(const std::filesystem::path& path, std::error_code* outEc = nullptr);

}
