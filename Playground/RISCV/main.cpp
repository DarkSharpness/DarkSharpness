#include "cpu.h"
#include "ram.h"
#include "icache.h"
#include "memctrl.h"
#include "ifetch.h"
#include <iostream>


signed main() {
    using dark::synchronize;
    dark::cpu      *cpu = new dark::cpu;
    dark::ram      *mem = new dark::ram;
    cpu->mem_in         = mem->mem_in;
    cpu->io_buffer_full = mem->io_buffer_full;
    mem->mem_out        = cpu->mem_out;
    mem->mem_addr       = cpu->mem_addr;
    mem->mem_wr         = cpu->mem_wr;

    cpu->init();
    mem->read();

    dark::reset = true;
    dark::ready = false;

    for (int i = 0, t = 10 ; i < t ; ++i) {
        cpu->work();
        mem->work();
        synchronize(*cpu);
        synchronize(*mem);
    }

    std::cerr << "Reset done.\n\n";

    dark::reset = false;
    dark::ready = true;
    dark::clock = true;
    dark::stall = true;
    std::size_t count = 0;
    do {
        cpu->work();
        mem->work();
        synchronize(*cpu);
        synchronize(*mem);
        ++count;
    } while(!dark::stall);

    std::cerr << "Total cycles: " << count << "\n";
    return 0;
}
