#include "cpu.h"
#include "ram.h"
#include <memory>
#include <fstream>

void run_simulator() {
    using dark::synchronize;

    auto cpu = std::make_unique <dark::cpu> ();
    auto mem = std::make_unique <dark::ram> ();


    cpu->mem_in         = mem->mem_in;
    cpu->io_buffer_full = mem->io_buffer_full;
    mem->mem_out        = cpu->mem_out;
    mem->mem_addr       = cpu->mem_addr;
    mem->mem_wr         = cpu->mem_wr;


    { // Initialize.
        cpu->init();
        std::ifstream file_input ("test.tmp");
        mem->read(file_input);
    } // End of initialization.


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
        dark::details("Cycle: ", ++dark::clock);
        cpu->work();
        mem->work();
        synchronize(*cpu);
        synchronize(*mem);
        dark::details(' ');
        if (dark::clock > 100000000) throw std::runtime_error("Too many cycles!");
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
    std::cerr << "Total cycles: " << dark::clock << "\n";
    return 0;
}
