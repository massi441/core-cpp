#pragma once

#ifndef NN_SWITCH

#include <filesystem>

#include "Core/Result/ReturnCode.h"

namespace ml {

template <typename ... Args>
std::filesystem::path fromCurrentPath(Args... args) {
    std::filesystem::path path = std::filesystem::current_path();
    (path.append(std::forward<Args>(args)), ...);
    return path;
}

template <typename ...Args>
std::filesystem::path makePath(Args&& ...args) {
    std::filesystem::path path;
    (path.append(std::forward<Args>(args)), ...);
    return path;
}

template <typename ... Args>
std::filesystem::path fromParentPath(const std::filesystem::path& basePath, Args&& ...args) {
    std::filesystem::path path = basePath.parent_path();
    (path.append(std::forward<Args>(args)), ...);
    return path;
}

bool ensureDirCreated(const std::filesystem::path& path);
bool clearDirectory(const std::filesystem::path& path);
bool removeDirectory(const std::filesystem::path& path);
bool isExistPath(const std::filesystem::path& path);
bool isExistParentPath(const std::filesystem::path& path);
bool createDirectory(const std::filesystem::path& path, std::error_code* outEc = nullptr);
ml::ReturnCode copyRecursiveOverwrite(const std::filesystem::path& from, const std::filesystem::path& to);

/**
 * Backups a directory by copying numbered versions into a destination directory,
 * in ascending order of recency.
 * @param source The folder to back-up
 * @param backupsDest The folder where numbered backups are stores
 * @param depth The amount of backups that should be stored in the destination folder
 * @return True if the full operation was successful, false otherwise.
 */
bool backupDirNumbered(const std::filesystem::path& source, const std::filesystem::path& backupsDest, uint32_t depth);

}

#endif
