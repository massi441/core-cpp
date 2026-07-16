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

    virtual uint readUInt32(const char* entryName) const = 0;
    virtual int readInt32(const char* entryName) const = 0;
    virtual float readFloat(const char* entryName) const = 0;
    virtual double readDouble(const char* entryName) const = 0;
    virtual const char* readString(const char* entryName) const = 0;

    virtual ScopedDataSource readInner(const char* entryName) const = 0;

    virtual ScopedDataSourceArray toArray(const char* entryName) const = 0;
    virtual ScopedDataSourceArray toArray() const = 0;

    virtual ~DataSource() = default;
};

class DataSourceArray {
public:
    DataSourceArray() = default;

    virtual size_t size() const = 0;
    virtual ScopedDataSource next() = 0;
    virtual bool hasNext() const = 0;
    virtual ScopedDataSource operator[](size_t i) const = 0;
    virtual ~DataSourceArray() = default;

    ScopedDataSource safeAt(size_t i) const {
        if (i >= this->size()) {
            return nullptr;
        }

        return this->operator[](i);
    }

    class Iterator {
    public:
        explicit Iterator(DataSourceArray* array, ScopedDataSource current) {
            mArray = array;
            mCurrent = std::move(current);
        }

        Iterator& operator++() {
            if (mArray->hasNext()) {
                mCurrent = mArray->next();
            } else {
                mCurrent = nullptr;
            }

            return *this;
        }

        DataSource* operator*() const {
            return mCurrent.get();
        }

        bool operator!=(const Iterator& other) const {
            return mCurrent != other.mCurrent;
        }

    private:
        DataSourceArray* mArray;
        ScopedDataSource mCurrent;
    };

    Iterator begin() {
        if (!this->hasNext()) {
            return this->end();
        }

        return Iterator(this, this->next());
    }

    Iterator end() {
        return Iterator(this, nullptr);
    }
};

}
