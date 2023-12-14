#pragma once
#include "utility.h"
#include <cstdint>

namespace dark {

/**
 * @brief A random access memory.
 */
struct ram {
  public:
    using sync = sync_member_tag;

    static constexpr int width = 18;
    using storage_type = std::array <std::uint8_t, 1 << width>;

    storage_type data;

    wire mem_out;   // Input from cpu.
    wire mem_wr;    // Whether to write.
    wire mem_addr;  // Address to read/write.

  public:

    /**
     * @brief Output of RAM (Input of CPU).
     * If the input wire of cycle #x is set,
     * It will output the value of cycle #x + 1.
     * @return Requested byte of last cycle.
     */
    const wire mem_in = { [this] () -> int { return data[last_addr()]; } };
    /**
     * @return Always 0 (RAM is never full), currently.
     */
    const wire io_buffer_full = { [this] () -> int { return 0; } };

  public: // This part should be private.
    reg last_addr; // Address of last cycle.

  public:
    void read();
    void work();
};


void ram::read() { /* To be completed... */ }
void ram::work()  {
    unsigned __addr = mem_addr(); // Speed up by caching.
    assert(__addr < (1 << width), "Memory address out of range");
    if (mem_wr()) data[__addr] = mem_out();
    else          last_addr   <= __addr;
}


} // namespace dark
