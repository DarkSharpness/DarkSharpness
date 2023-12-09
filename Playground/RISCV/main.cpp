#include "cpu.h"
#include "memory.h"
#include "icache.h"
#include "memctrl.h"
#include "ifetch.h"
#include <iostream>


signed main() {
    dark::cpu       *cpu = new dark::cpu;
    dark::memory    *mem = new dark::memory;
    cpu->mem_in         = mem->mem_in();
    cpu->io_buffer_full = mem->io_buffer_full();
    mem->mem_out        = cpu->mem_out();
    mem->mem_addr       = cpu->mem_addr();
    mem->mem_wr         = cpu->mem_wr();
    cpu->init();
    std::cerr << "Done!\n";
    return 0;
}