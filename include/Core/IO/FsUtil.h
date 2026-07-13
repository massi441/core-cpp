#pragma once

#include <filesystem>

namespace ml {

std::filesystem::path fromCurrentPath(const char* entryName);

bool ensureDirCreated(const std::filesystem::path& path);
bool clearDirectory(const std::filesystem::path& path);
bool isExistPath(const std::filesystem::path& path);

}
