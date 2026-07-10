#pragma once

#include "Core/Util/Types.h"
#include <cstddef>

namespace ml {

/**
 * A pool for renting and reusing objects, allowing to reduce memory allocations.
 * @tparam TPoolType The type of element stored by the pool (an Array, a connection...)
 */
template <typename TPoolType>
class Pool {
public:
    virtual TPoolType rent(size_t requestedSize) = 0;
    virtual TPoolType rent(size_t requestedSize, ml::byte maxOverflowCount) = 0;
    virtual bool release(TPoolType buffer) = 0;
    virtual ~Pool() {}
};

}
