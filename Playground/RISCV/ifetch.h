#pragma once
#include "utility.h"
#include "icache.h"
#include <cstring>

namespace dark {

struct ifetch_input {
    // Case 1: hit
    // Case 2: miss and rely on fetch.
    wire hit;       // icache hit.
    wire instData;  // Instruction fetched from cache.

    wire brDone;    // Compress enable and branch result.
    wire jalrDone;  // Compress enable and  jump  result.
    wire commitPc;  // PC of commit from RoB.

    wire insAvail;  // Instruction queue not full.
};

struct ifetch_output {
    reg pc;         // Program counter. (icache)
    reg insDone;    // Whether fetched.
    reg insOut;     // Instruction fetched.
    reg insPc;      // Instruction PC (next command).
};

struct ifetch_private {
    reg stall;      // Stall on jalr only.
    reg pause;      // Pause on end command.
};

struct history_table {
    static constexpr int width = 12;
    std::array <char, 1 << width> table;
};


struct ifetch : public ifetch_input, ifetch_output, private ifetch_private, history_table {
  public:
    using sync = sync_tag <ifetch_output, ifetch_private, history_table>;
    friend class caster <ifetch>;

  private:

    static int jalImm(int ins) {
        return sign_extend(bits {
            take <31> (ins) , take <19, 12> (ins) , take <20> (ins) , take <30, 21> (ins) , bits <1> (0)
        });
    }
    static int brImm(int ins) {
        return sign_extend(bits {
            take <31> (ins) , take <7> (ins) , take <30, 25> (ins), take <11,8> (ins) , bits <1> (0)
        });
    }

    int predictOff(int ins) const {
        return take <1> (table[take <width + 1, 2> (jalImm(ins))]) ? brImm(ins) : 4;
    }

  public:
    void work();


};

} // namespace dark

namespace dark {

void ifetch::work() {
    if (reset) {
        table   = {};
    } else if (!ready) {
        // Do nothing.
    } else if (brDone()) {
        auto &__data = table[take <width + 1, 2> (commitPc())];
        if (take <1> (commitPc())) {
            switch(__data) {
                default: assert(false);
                case 0: __data = 1; break;
                case 1: __data = 2; break;
                case 2: __data = 3; break;
                case 3: __data = 3; break;
            }
        } else {
            switch(__data) {
                default: assert(false);
                case 0: __data = 0; break;
                case 1: __data = 0; break;
                case 2: __data = 1; break;
                case 3: __data = 2; break;
            } return;
        }
    }

    if (reset) {
        pc      <= 0;
        pause   <= 0;
        stall   <= 0;
        insDone <= 0;
    } else if (!ready) {
        // Do nothing.
    } else if (brDone() && !take <0> (commitPc())) { // Wrong prediction.
        pc      <= bits {take <31,2> (commitPc()) , bits <2> (0)};
        pause   <= 0;
        stall   <= 0;
        insDone <= 0;
    } else if (hit() && insAvail() && !stall() && !pause()) {
        // Special judge.
        int __instData = instData();
        details("Instruction fetched: ", int_to_hex(__instData) , " at ", int_to_hex(pc()));
        if (__instData == 0x0ff00513) {
            pause   <= 1;
            insDone <= 1;
            insOut  <= 0b1100111; // Jump to address 0, meaningless.
            return void (debug("End command detected!"));
        }

        switch (take <6,0> (__instData)) {
            case 0b1101111: // Jump and link.
                pc <= pc() + jalImm(__instData); break;
            case 0b1100011: // Branching.
                pc <= pc() + predictOff(__instData); break;
            case 0b1100111: // Jump and link register.
                stall <= 1; break;
            default: // Non-branching, normal case.
                pc <= pc() + 4;
        }

    } else {
        insDone <= 0;   // Set to not done.
    }
}

} // namespace dark
