#pragma once

#include "Core/Data/DataSource.h"

namespace ml {

class DataSourceArray {
public:
    virtual size_t size() const = 0;
    virtual ScopedDataSource next() = 0;
    virtual bool hasNext() const = 0;
    virtual ScopedDataSource operator[](size_t i) const = 0;

    ScopedDataSource safeAt(size_t i) const {
        if (i >= this->size()) {
            return nullptr;
        }

        return this->operator[](i);
    }
};

}
