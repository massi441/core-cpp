#pragma once

#include <concepts>

#include <cstdint>

namespace ml {

template <typename T>
concept SerializableType = requires(const T& t, void* dest) {
    { t.serialize(dest) } -> std::same_as<uint64_t>;
};

template <typename T>
concept DeserializableType = requires(T& t, const void* src) {
    { t.deserialize(src) } -> std::same_as<void>;
};

class Serializer {
public:
    template <SerializableType T>
    static uint64_t Serialize(const T& src, void* dest) {
        return src.serialize(dest);
    }

    template <DeserializableType T>
    static void Deserialize(T* outValue, const void* src) {
        outValue->deserialize(src);
    }

    template <DeserializableType T>
    static T Deserialize(const void* source) {
        T value = T();
        value.deserialize(source);
        return value;
    }

private:
    Serializer() = delete;
};

}
