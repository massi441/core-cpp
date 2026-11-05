#pragma once

#include <cmath>
#include <optional>
#include <span>

namespace ml {

/**
 * A container for holding a view into a paginated buffer
 * @tparam T The type of element stored in the buffer
 */
template <typename T>
class PagedList {
public:
    PagedList() = default;

    explicit PagedList(std::span<T> entries, size_t pageSize) {
        mEntries = entries;
        mPageSize = pageSize;
    }

    std::optional<std::span<T>> getPage(size_t pageIndex) const {
        if (mPageSize == 0) {
            return std::nullopt;
        }

        size_t pageStart = pageIndex * mPageSize;

        if (pageStart >= mEntries.size()) {
            return std::nullopt;
        }

        size_t entryCount = std::min(mEntries.size() - pageStart, mPageSize);

        return mEntries.subspan(pageStart, entryCount);
    }

    size_t getPageSize() const {
        return mPageSize;
    }

    void setPageSize(size_t pageSize) {
        mPageSize = pageSize;
    }

    /**
     * Returns the amount of pages in the buffer, based on the current page size
     */
    size_t getPageCount() const {
        if (mPageSize == 0) {
            return 0;
        }

        return static_cast<size_t>(std::ceil(static_cast<double>(mEntries.size()) / mPageSize));
    }

private:
    std::span<T> mEntries;
    size_t mPageSize = 0;
};

}
