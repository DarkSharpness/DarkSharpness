#include "cpu.h"
#include "ram.h"
#include <memory>
#include <fstream>

std::size_t count = 0; // Count the total cycles.

void run_simulator() {
    // freopen("cache.tmp","w",stderr);
    std::ifstream file_input ("test.tmp");
    using dark::synchronize;
    auto cpu = std::make_unique <dark::cpu> ();
    auto mem = std::make_unique <dark::ram> ();
    // dark::ram      *mem = new dark::ram;
    cpu->mem_in         = mem->mem_in;
    cpu->io_buffer_full = mem->io_buffer_full;
    mem->mem_out        = cpu->mem_out;
    mem->mem_addr       = cpu->mem_addr;
    mem->mem_wr         = cpu->mem_wr;

    cpu->init();
    mem->read(file_input);

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
    dark::stall = false;
    do {
        dark::details("Cycle: ", ++count);
        cpu->work();
        mem->work();
        synchronize(*cpu);
        synchronize(*mem);
        dark::details(' ');
        if (count > 100000000) throw std::runtime_error("Too many cycles!");
    } while(!dark::stall);

    std::cerr << "Result: ";
    std::cout << cpu->return_value() << std::endl;
}


signed main() {
    try {
        run_simulator();
    } catch(const std::exception& e) {
        std::cerr << "\033[33m- Error: " << e.what() << " -\033[0m\n";
    }
    std::cerr << "Total cycles: " << count << "\n";
    return 0;
}
