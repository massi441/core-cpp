#ifndef NN_SWITCH

#include "Core/IO/FsUtil.h"

namespace fs = std::filesystem;

namespace ml {

bool ensureDirCreated(const fs::path &path) {
    std::error_code ec;
    if (fs::exists(path, ec)) {
        return true;
    }

    return fs::create_directory(path, ec);
}

bool clearDirectory(const fs::path &path) {
    std::error_code ec;

    std::vector<fs::path> removeableEntries;
    for (const fs::directory_entry& entry : fs::directory_iterator(path, ec)) {
        if (ec) {
            return false;
        }

        removeableEntries.push_back(entry.path());
    }

    for (const fs::path& removeableEntry : removeableEntries) {
        fs::remove_all(removeableEntry, ec);
        if (ec) {
            return false;
        }
    }

    return !ec;
}

bool removeDirectory(const std::filesystem::path &path) {
    std::error_code ec;
    fs::remove_all(path, ec);
    return !ec;
}

bool isExistPath(const fs::path &path) {
    std::error_code ec;
    return fs::exists(path, ec);
}

bool isExistParentPath(const std::filesystem::path& path) {
    fs::path parentPath = path.parent_path();

    return !parentPath.empty() && ml::isExistPath(parentPath);
}

// what the f is this shit
bool createDirectory(const fs::path &path, std::error_code* outEc) {
    std::error_code fb_ec;
    std::error_code& ec = outEc ? *outEc : fb_ec;

    fs::create_directory(path, ec);

    return !ec;
}

}

#endif

