#pragma once

#include "Core/Util/Types.h"

#include <cstdint>
#include <memory>

namespace ml {

class DataSource;
using ScopedDataSource = std::unique_ptr<DataSource>;

class DataSourceArray;
using ScopedDataSourceArray = std::unique_ptr<DataSourceArray>;

class DataSource {
public:
    DataSource() = default;

    virtual bool isValid() const = 0;

    virtual uint readUInt32(const char* entryName) = 0;
    virtual int readInt32(const char* entryName) = 0;
    virtual float readFloat(const char* entryName) = 0;
    virtual double readDouble(const char* entryName) = 0;
    virtual const char* readString(const char* entryName) = 0;

    virtual ScopedDataSource readInner(const char* entryName) = 0;
    virtual ScopedDataSourceArray toArray(const char* entryName) = 0;
};

}
