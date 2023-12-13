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
    wire brData;    // PC of a branch/jalr.

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

    int jalImm() {
        auto val = instData();
        return sign_extend(bits {
            take <31> (val) , take <19, 12> (val) , take <20> (val) , take <30, 21> (val) , bits <1> (0)
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
    } else if (ready) {
        if (hit() && insAvail() && !stall()) {
            insDone <= 1;
            insOut  <= instData();
            insPc   <= pc();

            switch (take <6,0> (instData())) {
                case 0b1101111: // Jump and link.
                    pc <= pc() + jalImm();
                    break;

                case 0b1100011: // Branching, wait until done.
                case 0b1100111: // Jump and link register.
                    stall <= 1;
                    break;

                default: // Non-branching, normal case.
                    pc <= pc() + 4;
            }
        }

        if (auto __brType = brType(); take <1> (__brType)) {
            stall <= 0;
            pc    <= brData();
        }
    }
}

} // namespace dark