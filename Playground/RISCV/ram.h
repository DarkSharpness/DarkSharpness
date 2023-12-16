#pragma once
#include "utility.h"
#include <cstdint>
#include <iostream>
#include <fstream>

#ifdef _SAFE
#include <unordered_map>
#endif

namespace dark {

/**
 * @brief A random access memory.
 */
struct ram {
  public:
    static constexpr int width = 18;
#ifdef _SAFE
    using storage_type = std::unordered_map <std::uint32_t, std::uint8_t>;
#else
    using storage_type = std::array <std::uint8_t, 1 << width>;
#endif
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
    const wire mem_in = {
        [this] () -> int {
            if (last_addr() >> 16 == 0x3) {
                uint8_t __byte; /* Read one byte from memory. */
                in >> __byte;
                return __byte;
            } else {
                return data[last_addr()];
            }
        }
    };
    /**
     * @return Always 0 (RAM is never full), currently.
     */
    const wire io_buffer_full = { [this] () -> int { return 0; } };

  private: // This part should be private.
    reg last_addr; // Address of last cycle.
    std::ifstream in  {"test.in"};
    std::ofstream out {"test.out"};

  public:
    void read(std::istream &in);
    void work();
    void sync() { last_addr.sync(); }
};


void ram::read(std::istream &in) {
    using buffer_type = char[16];
    buffer_type buf;
    std::string str;
    size_t  idx = 0;
    while(in >> buf) {
        if(buf[0] == '@') {
            idx = std::stoi(str = buf + 1, nullptr, 16);
        } else {
            data[idx++] = std::stoi(str = buf, nullptr, 16);
        }
    }
}


void ram::work()  {
    unsigned __addr = mem_addr(); // Speed up by caching.
    assert(__addr < (1 << width), "Memory address out of range");
    if (mem_wr()) {
        data[__addr] = mem_out();
        // Output if writing to given high address.
        if (__addr >> 16 == 0x3) out << (char)mem_out();
    } else last_addr <= __addr;
}


} // namespace dark
