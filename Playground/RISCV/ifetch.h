#pragma once
#include "utility.h"
#include "icache.h"

namespace dark {


struct ifetch {
  public:
    static constexpr int width = 8;             // Branch prediction width.
    static constexpr int size  = 1 << width;    // Branch prediction size.


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

  public:

    reg pc;         // Program counter.
    reg insDone;    // Whether fetched.
    reg insOut;     // Instruction fetched.
    reg insPc;      // Instruction PC (next command).
    reg insJump;    // Jump or not (branching).

  private:
    reg table[size]; // Branch history table.

    bool issueable() { return !(rsFull() || lsbFull() || robFull()); }
    bool predJump()  { return table[take <width + 1,2> (pc())](); }

    int jalImm() {
        union jal {
            int imm;
            struct {
                unsigned opcode     : 7;
                unsigned rd         : 5;
                unsigned imm_19_12  : 8;
                unsigned imm_11     : 1;
                unsigned imm_10_1   : 10;
                unsigned imm_20     : 1;
            };
            int data() const {
                return sign_extend <20> (
                    imm_20 << 20 | imm_19_12 << 12 | imm_11 << 11 | imm_10_1 << 1
                );
            }
        };
        static_assert(sizeof(jal) == 4);
        return jal { .imm = instData() }.data();
    }

    int brImm() {
        union br {
            int imm;
            struct {
                unsigned opcode     : 7;
                unsigned imm_11     : 1;
                unsigned imm_4_1    : 4;
                unsigned funct3     : 3;
                unsigned rs1        : 5;
                unsigned rs2        : 5;
                unsigned imm_10_5   : 6;
                unsigned imm_12     : 1;
            };
            int data() const {
                return sign_extend <12> (
                    imm_12 << 12 | imm_11 << 11 | imm_10_5 << 5 | imm_4_1 << 1
                );
            }
        };
        static_assert(sizeof(br) == 4);
        return br { .imm = instData() }.data();
    }


  public:
    void init(std::vector <wire> vec) {
        assert(vec.size() == 9);
        rsFull      = vec[0];
        lsbFull     = vec[1];
        robFull     = vec[2];
        hit         = vec[3];
        instData    = vec[4];
        robEn       = vec[5];
        robPc       = vec[6];
        brType      = vec[7];
        brPc        = vec[8];
    }

    void work() {
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

    void sync();
};


} // namespace dark
