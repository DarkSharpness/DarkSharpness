#pragma once
#include "utility.h"

#include "icache.h"
#include "memctrl.h"

namespace dark {

struct cpu {
  public:
    using sync = sync_tag <void>;

    wire mem_in;
    wire io_buffer_full;

    reg pc;

  public:
    // Internal components.

    memctrl ctrl;
    icache cache;

  public:

    const wire mem_out  = ctrl.mem_out;
    const wire mem_addr = ctrl.mem_addr;
    const wire mem_wr   = ctrl.mem_wr;

  public:

    void init();
    void work();
};

// Link the wires.
void cpu::init() {}
void cpu::work() {}




} // namespace dark