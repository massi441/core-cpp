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

ml::ReturnCode copyRecursiveOverwrite(const std::filesystem::path& from, const std::filesystem::path& to) {
    std::error_code ec;
    fs::copy_options options = fs::copy_options::recursive | fs::copy_options::overwrite_existing;

    if (!ml::clearDirectory(to)) {
        return "Failed to clear directory before copying";
    }

    fs::copy(from, to, options, ec);
    return !ec;
}

bool backupDirNumbered(const std::filesystem::path& source, const std::filesystem::path& backupsDest, uint32_t depth) {
    std::error_code ec;
    if (ml::isExistPath(backupsDest)) {
        // remove oldest back up (if present)
        fs::path maxBackupPath = backupsDest / std::to_string(depth);

        if (ml::isExistPath(maxBackupPath)) {
            fs::remove_all(maxBackupPath, ec);

            if (ec) {
                return false;
            }
        }

        // shift all back up folder numbers up by one (starting at the second to last backup)
        for (uint32_t i = depth - 1; i > 0; i--) {
            fs::path backupPath = backupsDest / std::to_string(i);
            fs::path newBackupPath = backupsDest / std::to_string(i + 1);

            if (!ml::isExistPath(backupPath)) {
                continue;
            }

            fs::rename(backupPath, newBackupPath, ec);

            if (ec) {
                return false;
            }
        }
    } else if (!fs::create_directory(backupsDest, ec)) {
        return false;
    }

    fs::path newestBackupPath = backupsDest / std::to_string(1);
    fs::copy_options options = fs::copy_options::recursive | fs::copy_options::overwrite_existing;

    fs::copy(source, newestBackupPath, options, ec);

    return !ec;
}

}

#endif

