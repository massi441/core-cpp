#pragma once

#include <cstddef>
#include <cstdint>

namespace ml {

class MemorySize {
public:
    static constexpr size_t B = 1;
    static constexpr size_t KB = B * 1024;
    static constexpr size_t MB = KB * 1024;
    static constexpr size_t GB = MB * 1024;

    /**
     * Converts a byte amount into bytes (identity conversion)
     * @param amount The amount of bytes
     * @return The same amount of bytes
     */
    static constexpr size_t Bytes(uint32_t amount) { return amount; }

    /**
     * Converts a kilobyte amount into bytes
     * @param amount The amount of kilobytes to convert
     * @return The amount of bytes from the amount of kilobytes provided
     */
    static constexpr size_t KiloBytes(uint32_t amount) { return amount * KB; }

    /**
     * Converts a megabyte amount into bytes
     * @param amount The amount of megabytes to convert
     * @return The amount of bytes from the amount of megabytes provided
     */
    static constexpr size_t MegaBytes(uint32_t amount) { return amount * MB; }

    /**
     * Converts a gigabyte amount into bytes
     * @param amount The amount of gigabytes to convert
     * @return The amount of bytes from the amount of gigabytes provided
     */
    static constexpr size_t GigaBytes(uint32_t amount) { return amount * GB; }

private:
    MemorySize() = default;
};

}