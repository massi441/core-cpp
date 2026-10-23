#pragma once

#include <concepts>
#include <type_traits>

template <typename T>
concept EnumClass = std::is_enum_v<T> && !std::is_convertible_v<T, std::underlying_type_t<T>>;
