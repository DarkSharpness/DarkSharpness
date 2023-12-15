#pragma once
#include "utility.h"
#include "icache.h"

namespace dark {

struct ifetch_input {
    // Case 1: hit
    // Case 2: miss and rely on fetch.
    wire hit;       // icache hit.
    wire instData;  // Instruction fetched from cache.

    // Update value after write_back.
    wire brDone;    // Compress enable and jump result.
    wire brData;    // New PC of a jalr destination.

    wire insAvail;  // Instruction queue not full.
};

struct ifetch_output {
    reg pc;         // Program counter. (icache)
    reg insDone;    // Whether fetched.
    reg insOut;     // Instruction fetched.
    reg insPc;      // Instruction PC (next command).
};

struct ifetch_private {
    reg stall;      // Stall on jalr/branch.
    reg pause;      // Pause on end command.
};

struct ifetch : public ifetch_input, ifetch_output, private ifetch_private {
  public:
    using sync = sync_tag <ifetch_output>;
    friend class caster <ifetch>;

  private:

    static int jalImm(int ins) {
        // auto ins = instData();
        return sign_extend(bits {
            take <31> (ins) , take <19, 12> (ins) , take <20> (ins) , take <30, 21> (ins) , bits <1> (0)
        });
    }

  public:
    void work();
};

} // namespace dark

namespace dark {

void ifetch::work() {
    if (reset) {
        pc      <= 0;
        pause   <= 0;
        insDone <= 0;
    } else if (!ready) {
        // Do nothing.
    } else if(hit() && insAvail() && !stall() && !pause()) {
        // Special judge.
        int __instData = instData();
        if (__instData == 0x0ff00513) {
            pause   <= 1;
            insDone <= 1;
            insOut  <= 0b1100111; // Jump to address 0, meaningless.
            return void (debug("End command detected!"));
        }

        insDone <= 1;
        insOut  <= instData();
        insPc   <= pc();

        switch (take <6,0> (__instData)) {
            case 0b1101111: // Jump and link.
                pc <= pc() + jalImm(__instData); break;
            case 0b1100011: // Branching, wait until done.
            case 0b1100111: // Jump and link register.
                stall <= 1; break;
            default: // Non-branching, normal case.
                pc <= pc() + 4;
        }
        details("Program counter:", pc());
    } else {
        insDone <= 0;   // Set to not done.
        if (brDone()) { // Wait for WB...
            stall <= 0;
            pc <= brData();
            if (pause()) { ::dark::stall = true; }
        }
    }
    debug("Program counter:", pc());
}

} // namespace dark
