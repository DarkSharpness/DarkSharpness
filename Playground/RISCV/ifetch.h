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
    wire brType;    // Compress enable and jump result.
    wire brData;    // New PC of a jalr destination.

    wire insAvail;  // Instruction queue not full.
};

struct ifetch_output {
    reg pc;         // Program counter. (icache)
    reg insDone;    // Whether fetched.
    reg insOut;     // Instruction fetched.
    reg insPc;      // Instruction PC (next command).
};


struct ifetch : public ifetch_input, ifetch_output {
  public:
    using sync = sync_tag <ifetch_output>;
    friend class caster <ifetch>;

  private:
    reg stall;      // Stall on branch and jalr.

    static int jalImm(int ins) {
        // auto ins = instData();
        return sign_extend(bits {
            take <31> (ins) , take <19, 12> (ins) , take <20> (ins) , take <30, 21> (ins) , bits <1> (0)
        });
    }
    static int brImm(int ins) {
        // auto ins = instData();
        return sign_extend(bits {
            take <31> (ins) , take <7> (ins) , take <30, 25> (ins), take <11,8> (ins) , bits <1> (0)
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
        insDone <= 0;
    } else if (!ready) {
        // Do nothing.
    } else if(hit() && insAvail() && !stall()) {
        insDone <= 1;
        insOut  <= instData();
        insPc   <= pc();
        switch (take <6,0> (instData())) {
            case 0b1101111: // Jump and link.
                pc <= pc() + jalImm(instData()); break;
            case 0b1100011: // Branching, wait until done.
            case 0b1100111: // Jump and link register.
                stall <= 1; break;
            default: // Non-branching, normal case.
                pc <= pc() + 4;
        }
    } else {
        insDone <= 0;
        if (auto __brType = brType()) { // Wait for WB.
            stall  <= 0;
            if (take <1> (__brType)) { // Branch.
                pc <= pc() + (take <0> (__brType) ? brImm(instData()) : 4); 
            } else { // Jump and link register.
                pc <= brData();
            }
        }
    }
}

} // namespace dark