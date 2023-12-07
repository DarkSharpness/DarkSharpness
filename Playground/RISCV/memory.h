#pragma once
#include "utility.h"

namespace dark {

struct memory {
    static constexpr int width = 18;
    char data[1 << width];

    wire mem_out;   // Input from cpu.
    wire mem_wr;    // Whether to write.
    wire mem_addr;  // Address to read/write.

    // Output to cpu.
    wire mem_in() { return { [this] ()  { return data[mem_addr()]; } }; }
    // Whether the buffer is full.
    wire io_buffer_full() { return { [this] ()  { return 0; } }; }

  private:
    reg last_addr;

  public:

    void work() {
        if (mem_wr()) data[mem_addr()] = mem_out();
        last_addr <= mem_addr();
    }

    void sync() { last_addr.sync(); }
};


} // namespace dark
