#pragma once

#include "Core/Util/Types.h"

namespace ml {

struct ArrayPoolConfig {
    ushort arrayMinSize = 16;
    ushort totalBuckets = 12;
    ushort maxOverflow = 0;
    ushort arraysPerBucket = 3;
    byte arrayGrowPower = 2;

    ArrayPoolConfig& withMinSize(ushort size) {
        this->arrayMinSize = size;
        return *this;
    }

    ArrayPoolConfig& withBuckets(ushort buckets) {
        this->totalBuckets = buckets;
        return *this;
    }

    ArrayPoolConfig& withGrowPower(ushort growPower) {
        this->arrayGrowPower = growPower;
        return *this;
    }

    ArrayPoolConfig& withBucketSize(ushort bucketSize) {
        this->arraysPerBucket = bucketSize;
        return *this;
    }
};

}
