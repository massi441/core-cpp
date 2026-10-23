#pragma once

#include <iterator>

#define ASSERT_SIZE(Item, Size) static_assert(std::size(Item) == Size)
#define ASSERT_SIZE_MESSAGE(Item, Size, Message) static_assert(std::size(Item) == Size, Message)
