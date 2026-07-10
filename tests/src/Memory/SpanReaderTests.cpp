#include <catch2/catch_test_macros.hpp>

#include "Core/Memory/SpanReader.h"

TEST_CASE("Reads 3 integers") {
    // Arrange
    int nums[] = {1, 2, 3};

    ml::SpanReader reader = ml::SpanReader(&nums);

    // Act
    int num1 = reader.readInt32();
    int num2 = reader.readInt32();
    int num3 = reader.readInt32();

    // Assert
    REQUIRE(num1 == nums[0]);
    REQUIRE(num2 == nums[1]);
    REQUIRE(num3 == nums[2]);
}
