#pragma once
#include "utility.h"

#include "icache.h"
#include "memctrl.h"

namespace dark {

struct cpu {
    wire mem_in;
    wire io_buffer_full;

    reg pc;

  private:

    memctrl ctrl;
    icache cache;

  public:

    wire mem_out()  { return ctrl.mem_out;  }
    wire mem_addr() { return ctrl.mem_addr; }
    wire mem_wr()   { return ctrl.mem_wr;   }

  public:
    void init() {

    }

    void work() {

    }

    void sync() {

    }


};



} // namespace dark