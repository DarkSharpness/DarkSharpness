#pragma once
#include "utility.h"
#include <cstdint>

namespace dark {

/**
 * @brief A random access memory.
 */
struct memory {
    static constexpr int width = 18;
    std::uint8_t data[1 << width];  // Data storage.

    wire mem_out;   // Input from cpu.
    wire mem_wr;    // Whether to write.
    wire mem_addr;  // Address to read/write.

    /**
     * @brief Output of RAM (Input of CPU).
     * If the input wire of cycle #x is set,
     * It will output the value of cycle #x + 1.
     * @return Requested byte of last cycle.
     */
    wire mem_in() { return { [this] () -> int { return data[last_addr()]; } }; }
    /**
     * @return Always 0 (RAM is never full), currently.
     */
    wire io_buffer_full() { return { [this] () ->int { return 0; } }; }

  private:
    reg last_addr; // Address of last cycle.

  public:

    void work() {
        unsigned __addr = mem_addr(); // Speed up by caching.
        if (__addr >> width)
            throw std::runtime_error("Memory overflow");

        if (mem_wr()) data[__addr] = mem_out();
        else          last_addr <= __addr;
    }

    void sync() { last_addr.sync(); }
};


} // namespace dark
