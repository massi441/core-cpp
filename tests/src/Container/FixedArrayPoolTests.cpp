#include "Core/Container/ArrayPool.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("Sanitizes minimum size") {
    // Arrange
    struct SizeSanityTest {
        ml::byte growPower;
        ml::ushort minSize;
        ml::ushort expectedMinSize;
    };

    SizeSanityTest testCase = GENERATE(
        SizeSanityTest{ .growPower = 3, .minSize = 2, .expectedMinSize = 3 },
        SizeSanityTest{ .growPower = 3, .minSize = 9, .expectedMinSize = 9 },
        SizeSanityTest{ .growPower = 3, .minSize = 27, .expectedMinSize = 27 }, // edge case
        SizeSanityTest{ .growPower = 4, .minSize = 1, .expectedMinSize = 4 }, // verify clamp if minSize < growPower
        SizeSanityTest{ .growPower = 4, .minSize = 16, .expectedMinSize = 16 },
        SizeSanityTest{ .growPower = 4, .minSize = 20, .expectedMinSize = 64 }
    );

    ml::ArrayPoolConfig desiredConfig = ml::ArrayPoolConfig
    {
        .arrayMinSize = testCase.minSize,
        .arrayGrowPower = testCase.growPower
    };

    // Act
    ml::FixedByteArrayPool pool = ml::FixedByteArrayPool(desiredConfig);
    ml::ArrayPoolConfig actualConfig = pool.getConfig();

    // Assert
    REQUIRE(actualConfig.arrayMinSize == testCase.expectedMinSize);
    REQUIRE(actualConfig.arrayGrowPower == desiredConfig.arrayGrowPower);
    REQUIRE(actualConfig.totalBuckets == desiredConfig.totalBuckets);
}

TEST_CASE("Rents buffer big enough") {
    ml::ushort minimumSize = GENERATE(5, 10, 35, 50);

    ml::FixedByteArrayPool pool = ml::FixedByteArrayPool();

    ml::Array<ml::byte>* buffer = pool.rent(minimumSize);

    REQUIRE(buffer != nullptr);
    REQUIRE(buffer->size() >= minimumSize);
}

TEST_CASE("Reuses same buffer after releasing") {
    // Arrange
    ml::ushort minimumSize = GENERATE(10, 28, 55, 210);

    ml::FixedByteArrayPool pool = ml::FixedByteArrayPool();

    // Act
    ml::Array<ml::byte>* rentedBuffer = pool.rent(minimumSize);
    ml::Array<ml::byte>* previousBuffer = rentedBuffer;

    pool.release(rentedBuffer);
    rentedBuffer = pool.rent(minimumSize);

    // Assert
    REQUIRE(previousBuffer != nullptr);
    REQUIRE(rentedBuffer == previousBuffer);
}

TEST_CASE("Does not reuse same buffer") {
    // Arrange
    ml::ushort minimumSize = GENERATE(10, 28, 55, 210);

    ml::FixedByteArrayPool pool = ml::FixedByteArrayPool();

    // Act
    ml::Array<ml::byte>* rentedBuffer = pool.rent(minimumSize);
    ml::Array<ml::byte>* previousBuffer = rentedBuffer;

    rentedBuffer = pool.rent(minimumSize);

    // Assert
    REQUIRE(previousBuffer != nullptr);
    REQUIRE(rentedBuffer != previousBuffer);
}

TEST_CASE("Uses overflown buffer") {
    // Arrange
    struct OverflowTest {
        ml::ArrayPoolConfig config;
        ml::ushort requestedSize;
        ml::byte maxOverflow;
        ml::ushort expectedBufferSize;
    };

    OverflowTest testCase = GENERATE(
        OverflowTest{ .config = { .arrayMinSize = 2, .totalBuckets = 3, .arraysPerBucket = 1, .arrayGrowPower = 2 }, .requestedSize = 2, .maxOverflow = 1, .expectedBufferSize = 4 },
        OverflowTest{ .config = { .arrayMinSize = 2, .totalBuckets = 3, .arraysPerBucket = 1, .arrayGrowPower = 2 }, .requestedSize = 2, .maxOverflow = 2, .expectedBufferSize = 8 }
    );

    ml::FixedByteArrayPool pool = ml::FixedByteArrayPool(testCase.config);

    ml::Array<ml::byte>* prefilled = pool.rent(testCase.expectedBufferSize);
    pool.release(prefilled);

    // Act
    ml::Array<ml::byte>* rentedBuffer = pool.rent(testCase.requestedSize, testCase.maxOverflow);

    // Assert
    REQUIRE(rentedBuffer != nullptr);
    REQUIRE(rentedBuffer->size() == testCase.expectedBufferSize);
}

