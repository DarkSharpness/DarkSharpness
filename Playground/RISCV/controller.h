#pragma once
#include "utility.h"

namespace dark {


struct controller_input {
    wire issue;     // Whether to issue.

    wire iType;     // Instruction type for ALU.
    wire ALUPc;     // Pc for ALU.

    wire immediate; // Immediate value.
    wire rdIndex;   // Index in register file.

    wire memDone;   // Load store is done, which will stop bubble.
};

struct controller_output {
    reg  wrWork;        // Whether to work.
    reg  wrType;        // Type for next writeback operation.

    reg  wbPc;          // Program counter for writeback.
    reg  wbImm;         // Immediate value for next operation.
    reg  wbRd;          // Register index for writing back.

    reg  isBubbling;    // Whether there is a bubble in this cycle.
};


/**
 * @brief Controller, which forward the data from decoder
 * to the MEM/WB controll unit after the ALU.
 * It work simultaneously with the ALU unit.
 * 
 */
struct controller : public controller_input, controller_output {
    using sync = sync_tag <controller_output>;
    friend class caster <controller>;

    /* Whether ther is a bubble this or next cycle. */
    const wire nextBubble = { [this]() -> int { return isBubbling() || isNewBubble(); } };

    void work() {
        if (reset) {
            wrType      <= 0;
            isBubbling  <= 0;
        } else if (!ready) {
            // Do nothing.
        } else {
            wrWork <= issue();
            wrType <= iType();

            wbPc   <= ALUPc();
            wbImm  <= immediate();
            wbRd   <= rdIndex();

            if (isBubbling()) {
                isBubbling <= !memDone();
            } else if (isNewBubble()) {
                isBubbling <= 1;
            }
        }
    }

  private:
    /* Whether there is a new bubble generating. */
    /* Whether this command is a memory related command. */
    bool isNewBubble() const { return issue() && ALU_type::isMemory(iType()); }
};


} // namespace dark
