#include "Core/IO/FsUtil.h"

namespace ml {

std::filesystem::path fromCurrentPath(const char* entryName) {
    std::filesystem::path path = std::filesystem::current_path();
    path /= entryName;
    return path;
}

bool ensureDirCreated(const std::filesystem::path &path) {
    std::error_code ec;
    if (std::filesystem::exists(path, ec)) {
        return true;
    }

    return std::filesystem::create_directory(path, ec);
}

bool clearDirectory(const std::filesystem::path &path) {
    std::error_code ec;

    std::vector<std::filesystem::path> removeableEntries;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path, ec)) {
        if (ec) {
            return false;
        }

        removeableEntries.push_back(entry.path());
    }

    for (const std::filesystem::path& removeableEntry : removeableEntries) {
        std::filesystem::remove_all(removeableEntry, ec);
        if (ec) {
            return false;
        }
    }

    return !ec;
}

bool isExistPath(const std::filesystem::path &path) {
    std::error_code ec;
    return std::filesystem::exists(path, ec);
}

}
