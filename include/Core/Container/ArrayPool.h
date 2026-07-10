#pragma once

#include <cmath>

#include "ArrayStack.h"
#include "Core/Container/Array.h"
#include "Core/Container/ArrayPoolConfig.h"
#include "Core/Container/Pool.h"
#include "Core/Util/MathHelpers.h"

namespace ml {

/**
 * A pool of reusable Array's
 * @tparam T The type stored by the array's
 */
template <typename T>
class ArrayPool : public Pool<Array<T>*> {
public:
    explicit ArrayPool() : ArrayPool(ArrayPoolConfig()) {}

    explicit ArrayPool(ArrayPoolConfig config) {
        ml::ushort arrayMinSize = mathi::max(config.arrayGrowPower, config.arrayMinSize);
        ushort minBuckets = mathi::powCeil(config.arrayGrowPower, arrayMinSize);

        mConfig.arrayMinSize = std::pow(config.arrayGrowPower, minBuckets);
        mConfig.totalBuckets = mathus::max(config.totalBuckets, minBuckets);
        mConfig.arrayGrowPower = config.arrayGrowPower;
        mConfig.arraysPerBucket = config.arraysPerBucket;

        mBuckets = ml::Array<Bucket>(mConfig.totalBuckets);

        for (Bucket& bucket : mBuckets) {
            bucket = Bucket(mConfig.arraysPerBucket);
        }
    }

    /**
     * Attempts to rent a fixed array of the nearest requested size from the current pool.
     * If no fixed array is found, a fallback array is allocated on the heap
     * @param requestedSize The minimum size of the fixed array
     * @return A pointer to a fixed array, that can later be returned to the pool
     */
    ml::Array<T>* rent(size_t requestedSize) override {
        uint64_t bufferSize = this->calcNearestBucketSize(requestedSize);
        uint64_t bucketIndex = this->calcBucketIndex(bufferSize);

        if (!mBuckets.isInBounds(bucketIndex)) {
            return new Array<T>(bufferSize);
        }

        Bucket& bucket = mBuckets[bucketIndex];

        ml::Array<T>* buffer;
        if (bucket.pop(&buffer)) {
            return buffer;
        }

        return new Array<T>(bufferSize);
    }

    /**
     * Attempts to rent a fixed array of the nearest requested size from the current pool,
     * falling back to larger buckets up to maxOverflowCount before allocating on the heap.
     * @param requestedSize The minimum size of the fixed array
     * @param maxOverflowCount The maximum number of larger buckets to try before heap allocating
     * @return A pointer to a fixed array, that can later be returned to the pool
     */
    ml::Array<T>* rent(size_t requestedSize, byte maxOverflowCount) override {
        uint64_t bucketSize = this->calcNearestBucketSize(requestedSize);
        uint64_t bucketIndex = this->calcBucketIndex(bucketSize);

        if (!mBuckets.isInBounds(bucketIndex)) {
            return new Array<T>(bucketSize);
        }

        uint64_t maxIndex = mathl::min(bucketIndex + maxOverflowCount, mBuckets.maxIndex());

        for (uint64_t i = bucketIndex; i <= maxIndex; i++) {
            Bucket& bucket = mBuckets[i];

            ml::Array<T>* buffer;
            if (bucket.pop(&buffer)) {
                return buffer;
            }
        }

        return new Array<T>(bucketSize);
    }

    /**
     * Returns a previously rented fixed array back to the pool.
     * If the corresponding bucket is full or the buffer size is out of pool range, the buffer is deleted.
     * @param buffer The buffer to return
     * @return True if the buffer was successfully returned to the pool, false if it was deleted
     */
    bool release(ml::Array<T>* buffer) override {
        uint64_t bucketIndex = this->calcBucketIndex(buffer->size());
        if (!mBuckets.isInBounds(bucketIndex)) {
            delete buffer;
            return false;
        }

        Bucket& bucket = mBuckets[bucketIndex];
        if (bucket.push(buffer)) {
            return true;
        }

        delete buffer;
        return false;
    }

    ~ArrayPool() override {
        for (Bucket& bucket : mBuckets) {
            ml::Array<T>* buffer;
            while (bucket.pop(&buffer)) {
                delete buffer;
            }
        }
    }

private:
    using Bucket = ml::ArrayStack<ml::Array<T>*>;

private:
    ArrayPoolConfig mConfig;
    ml::Array<Bucket> mBuckets;

    uint64_t calcNearestBucketSize(size_t requestedSize) const {
        return mathl::max(mConfig.arrayMinSize, std::pow(mConfig.arrayGrowPower, mathf::powCeil(mConfig.arrayGrowPower, requestedSize)));
    }

    uint64_t calcBucketIndex(size_t bucketSize) const {
        // min: 9, pow: 3 offset -> (log3(9) - 1) = (2 - 1) = 1
        uint64_t indexOffset = mathl::logBase(mConfig.arrayGrowPower, mConfig.arrayMinSize) - 1;

        return mathl::logBase(mConfig.arrayGrowPower, bucketSize) - 1 - indexOffset;
    }
};

}
