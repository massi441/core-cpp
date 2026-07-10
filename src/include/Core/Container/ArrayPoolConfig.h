#pragma once

#include "Core/Util/Types.h"

namespace ml {

struct ArrayPoolConfig {
    ml::ushort arrayMinSize = 16;
    ml::ushort totalBuckets = 12;
    ml::ushort maxOverflow = 0;
    ml::ushort arraysPerBucket = 3;
    ml::byte arrayGrowPower = 2;

    ArrayPoolConfig& withMinSize(ml::ushort size) {
        this->arrayMinSize = size;
        return *this;
    }

    ArrayPoolConfig& withBuckets(ml::ushort buckets) {
        this->totalBuckets = buckets;
        return *this;
    }

    ArrayPoolConfig& withGrowPower(ml::ushort growPower) {
        this->arrayGrowPower = growPower;
        return *this;
    }

    ArrayPoolConfig& withBucketSize(ml::ushort bucketSize) {
        this->arraysPerBucket = bucketSize;
        return *this;
    }
};

}
