#pragma once
#include "utility.h"

#include "alu.h"
#include "icache.h"
#include "memctrl.h"
#include "ifetch.h"
#include "decoder.h"
#include "register.h"
#include "controller.h"

namespace dark {

struct cpu_input {
    wire mem_in;
    wire io_buffer_full;
};
struct cpu_component {
    memctrl     memCtrl;
    icache      cache;

    ifetch      fetcher;
    decoder     decoder;

    controller  control;
    scalar_file scalars;
    scalar_ALU  scalarALU;
};


struct cpu : public cpu_input, private cpu_component {
  public:
    using sync = sync_tag <cpu_component>;
    friend class caster <cpu>;

    const wire mem_out  = memCtrl.mem_out;
    const wire mem_addr = memCtrl.mem_addr;
    const wire mem_wr   = memCtrl.mem_wr;

  public:

    void init();
    void work();
};

// Link the wires.
void cpu::init() {}
void cpu::work() {}




} // namespace dark