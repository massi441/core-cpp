#include <Core/Container/SequencedDictionary.h>

#include <catch2/catch_test_macros.hpp>
#include "Core/Util/Types.h"

using StringStore = ml::SequencedDictionary<ml::byte, std::string>;

TEST_CASE("Adds 3 elements") {
    // Arrange
    StringStore store = StringStore();

    std::string str1 = "String1";
    std::string str2 = "String2";
    std::string str3 = "String3";

    // Act
    StringStore::OptionalNode node1 = store.upload(str1);
    StringStore::OptionalNode node2 = store.upload(str2);
    StringStore::OptionalNode node3 = store.upload(str3);

    // Assert
    REQUIRE((node1.has_value() && node1->sequenceNumber == 0 && node1->value == str1));
    REQUIRE((node2.has_value() && node2->sequenceNumber == 1 && node2->value == str2));
    REQUIRE((node3.has_value() && node3->sequenceNumber == 2 && node3->value == str3));

    REQUIRE(store.size() == 3);
}

TEST_CASE("Adds N elements and removes 2") {
    // Arrange
    StringStore store = StringStore();
    std::string str = "MyString";
    ml::byte elementCount = 5;

    // Act
    for (ml::byte i = 0; i < elementCount; ++i) {
        store.upload(str);
    }

    // Assert
    REQUIRE(store.size() == elementCount);

    // Act
    StringStore::OptionalNode last = store.remove(elementCount - 1);
    StringStore::OptionalNode first = store.remove(0);

    // Assert
    REQUIRE((first.has_value() && first->sequenceNumber == 0));
    REQUIRE((last.has_value() && last->sequenceNumber == elementCount - 1));
    REQUIRE(store.size() == 3);
}

TEST_CASE("Rejects value when full") {
    // Arrange
    StringStore store = StringStore();
    std::string str = "MyString";

    // Act
    while (!store.isFull()) {
        StringStore::OptionalNode node = store.upload(str);
        REQUIRE(node.has_value());
    }

    StringStore::OptionalNode overflowNode = store.upload(str);

    // Assert
    REQUIRE(store.isFull());
    REQUIRE(overflowNode.has_value() == false);
}
