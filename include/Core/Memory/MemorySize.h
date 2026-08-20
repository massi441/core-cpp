#pragma once

#include <cstdint>
#include <cstddef>

namespace ml {

class MemorySize {
public:
    static constexpr size_t B = 1;
    static constexpr size_t KB = B * 1024;
    static constexpr size_t MB = KB * 1024;
    static constexpr size_t GB = MB * 1024;

    static constexpr size_t Bytes(uint32_t amount) { return amount; }
    static constexpr size_t KiloBytes(uint32_t amount) { return amount * KB; }
    static constexpr size_t MegaBytes(uint32_t amount) { return amount * MB; }
    static constexpr size_t GigaBytes(uint32_t amount) { return amount * GB; }

private:
    MemorySize() = default;
};

}
