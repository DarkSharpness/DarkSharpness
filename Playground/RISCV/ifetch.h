#pragma once
#include "utility.h"
#include "icache.h"

namespace dark {

struct ifetch_input {
    wire rsFull;    // Reservation station full.
    wire lsbFull;   // Load/store buffer full.
    wire robFull;   // Reorder buffer full.

    // Case 1: hit
    // Case 2: miss and rely on fetch.

    wire hit;       // icache hit.
    wire instData;  // Instruction fetched from cache.

    wire robEn;     // Reorder buffer enable.
    wire robPc;     // Reorder buffer PC.

    // Update branch history table.
    wire brType;    // Compress enable and jump result.
    wire brPc;      // PC of a branch.
};

struct ifetch_output {
    reg pc;         // Program counter.
    reg insDone;    // Whether fetched.
    reg insOut;     // Instruction fetched.
    reg insPc;      // Instruction PC (next command).
    reg insJump;    // Jump or not (branching).
};

struct ifetch_private {
    static constexpr int width = 8;             // Branch prediction width.
    static constexpr int size  = 1 << width;    // Branch prediction size.
    std::array <reg, size> table;               // Branch history table.
};

struct ifetch : ifetch_input, ifetch_output, ifetch_private {
  public:
    using tag = sync_tag <ifetch_output, ifetch_private>;

  private:
    bool issueable() { return !(rsFull() || lsbFull() || robFull()); }
    bool predJump()  { return table[take <width + 1,2> (pc())](); }

    int jalImm() {
        auto val = instData();
        return sign_extend(bits{
            take <31> (val) , take <19, 12> (val) , take <20> (val) , take <30, 21> (val) , bits <1> (0)
        });
    }

    int brImm() {
        auto val = instData();
        return sign_extend(bits{
            take <31> (val) , take <7> (val) , take <30, 25> (val)  , take <11, 8> (val) , bits <1> (0)
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
        if (hit() && issueable()) {
            insDone <= 1;
            insOut  <= instData();
            insPc   <= pc();

            switch (take <6,0> (instData())) {
                case 0b1101111: // Jump and link.
                    pc <= pc() + jalImm();
                    break;

                case 0b1100011:{// Branching
                    bool __predJump = predJump();
                    insJump <= __predJump;
                    pc <= pc() + (__predJump ? brImm() : 4);
                }   break;

                case 0b1100111: // Jump and link register.
                    static_cast <void> (NotImplemented());
                    break;

                default: // Non-branching, normal case.
                    pc <= pc() + 4;
            }
        }
    }

    // BHT update part.
    if (reset) {
        for (int i = 0; i < size; ++i) table[i] <= 0;
    } else if (ready) {
        if (take <1> (brType())) {
            table[take <width + 1, 2> (brPc())] <= take <0> (brType());
        }
    }
}

} // namespace dark