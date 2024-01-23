#pragma once
#include "utility.h"
#include <iostream>

namespace dark {


struct controller_input {
    wire issue;     // Whether to issue.

    wire iType;     // Instruction type for ALU.
    wire ALUPc;     // Pc for ALU.

    wire immediate; // Immediate value.
    wire rdIndex;   // Index in register file.

    wire memDone;   // Load store is done, which will stop bubble.
    wire rs1Data;   // Data of rs1. (For store).
    wire rs2Data;   // Data of rs2. (For store).
    wire vecDone;   // Whether vector operation is done.

    wire memStatus; // Status of the memctrl.

    wire dbgCmd;    // Debug command.
};

struct controller_output {
    reg  wrType;        // Type for next writeback operation.

    reg  wbPc;          // Program counter for writeback.
    reg  wbImm;         // Immediate value for next operation.
    reg  wbRd;          // Register index for writing back.
    reg  wbrs1;         // Data source 1.
    reg  wbrs2;         // Data source 2.

    reg  memType;       // Memory type.
    reg  memSize;       // Memory size.
    reg  stride;        // Stride of vector operation.

    reg  dbgOut;        // Debug command.
};

struct controller_private {
    reg  isMemory;      // Whether there is memory operation.
    reg  isVector;      // Whether there is vector operation.
};


/**
 * @brief Controller, which forward the data from decoder
 * to the MEM/WB controll unit after the ALU.
 * It work simultaneously with the ALU unit.
 * 
 */
struct controller : public controller_input, controller_output, private controller_private {
    using sync = sync_tag <controller_output, controller_private>;
    friend class caster <controller>;

    /* Whether ther is a bubble this or next cycle. */
    const wire nextBubble = [this]() -> int { return isMemory() || isVector() || isNewBubble(); };

    void work() {
        if (reset) {
            wrType      <= 0;
            isMemory    <= 0;
        } else if (!ready) {
            // Do nothing.
        } else {
            if (issue()) {
                dbgOut  <= dbgCmd();
                wrType  <= iType();
                wbPc    <= ALUPc();
                wbImm   <= immediate();
                wbRd    <= rdIndex();
                wbrs1   <= rs1Data();
                wbrs2   <= rs2Data();
            }

            bool __nextMemory = issue() && ALU_type::isMemory(iType());
            bool __nextVector = issue() && ALU_type::isVector(iType());

            if (isMemory()) {
                isMemory <= !memDone();
            } else {
                isMemory <= __nextMemory;
            }

            if (isVector()) {
                isVector <= !vecDone();
            } else {
                isVector <= __nextVector;
            }

            if (__nextMemory) {
                if (__nextVector) {
                    memType <= (ALU_type::isLoad(iType()) ? 4 : 5);
                    if (ALU_type::memOp(iType()) == 0b00) {
                        // Unit stride.
                        memSize <= 0b100;
                        stride  <= 4;
                    } else if (ALU_type::memOp(iType()) == 0b10) {
                        // Strided
                        switch (ALU_type::funct3_2(iType())) {
                            case 0b00: memSize <= 0b001; break;
                            case 0b01: memSize <= 0b010; break;
                            case 0b10: memSize <= 0b100; break;
                            default: assert(false, "Unknown memory size.");
                        }
                        stride  <= rs2Data();
                    } else {
                        assert(false, "Unknown memory operation.");
                    }
                } else { // Scalar load and store.
                    memType <= (ALU_type::isLoad(iType()) ? 2 : 3);
                    switch (ALU_type::funct3_2(iType())) {
                        case 0b00: memSize <= 0b001; break;
                        case 0b01: memSize <= 0b010; break;
                        case 0b10: memSize <= 0b100; break;
                        default: assert(false, "Unknown memory size.");
                    }
                }
            } else {
                // No memory operation newly issued
                // Reset the memory type if memctrl is working on current status.
                if (memType() == memStatus()) memType <= 0;
            }
        }
    }

  private:
    /* Generate new bubble is next command is vector command or memory command. */
    bool isNewBubble() const {
        return issue() && (ALU_type::isMemory(iType()) || ALU_type::isVector(iType()));
    }
};


} // namespace dark
