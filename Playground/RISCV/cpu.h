#pragma once
#include "utility.h"

#include "alu.h"
#include "icache.h"
#include "memctrl.h"
#include "ifetch.h"
#include "decoder.h"
#include "register.h"
#include "controller.h"
#include "writer.h"

namespace dark {

struct cpu_input {
    wire mem_in;
    wire io_buffer_full;
};
struct cpu_component {
    memctrl     memctrl;
};


struct cpu : public cpu_input, private cpu_component {
  public:
    using sync = sync_tag <cpu_component>;
    friend class caster <cpu>;

    const wire mem_out  = memctrl.mem_out;
    const wire mem_addr = memctrl.mem_addr;
    const wire mem_wr   = memctrl.mem_wr;

  public:

    void init();
    void work();
    // auto return_value() { return scalars.return_value() & 0xff; }
};

// Link the wires.
void cpu::init() {}

void cpu::work() {}

} // namespace dark
