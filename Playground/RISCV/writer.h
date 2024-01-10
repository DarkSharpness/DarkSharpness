#pragma once
#include "utility.h"


namespace dark {

struct writer_input {
    wire wrWork;        // Whether to work.
    wire wrType;        // Type for next writeback operation.

    wire wbPc;          // Program counter for writeback.
    wire wbImm;         // Immediate value for next operation.
    wire wbRd;          // Register index for writing back.

    wire scalarOut;     // Scalar output from ALU.

    wire memDone;       // Load store is done, which will stop bubble.
    wire loadData;      // Data loaded.

    wire    dbgCmd;    // Debug command.
};

struct writer_output {
    reg  brDone;        // Whether a branch/jalr is just done.
    reg  brData;        // The new PC of a branch/jalr destination.

    reg  wbDone;        // Whether a writeback is just done.
    reg  wbData;        // The data to write back to register file.
};

struct writer_private {
    reg status; // Status of the execution.
};

struct writer : public writer_input, writer_output, private writer_private {
    using sync = sync_tag <writer_output, writer_private>;
    friend class caster <writer>;

    void work();

  private:
    static constexpr int IDLE = 0, LOAD = 1;
    void work_idle();
};


} // namespace dark

namespace dark {

void writer::work() {
    if (reset) {
        brDone <= 0;
        wbDone <= 0;
        status <= IDLE;
    } else if (!ready) {
        // Do nothing.
    } else {
        /**
         * @brief Some comments:
         * The following kind of coding can not be used in the real
         * verilog. Actually, in real verilog, the 'Type' will be split
         * into several separate wires, and there will be another single
         * wire to indicate the type of the instruction.
         * 
         * When translating into verilog, be careful about this!
         */
        if (status() == IDLE) {
            if (wrWork()) {
                details("-- Writeback PC:", int_to_hex(wbPc()));
                work_idle();
            } else {
                brDone <= 0;
                wbDone <= 0;
            }
        } else { // Loading...
            if (memDone()) {
                status <= IDLE;
                wbDone <= wbRd();
                switch (ALU_type::funct3(wrType())) {
                    default: assert(false, "I give up..."); break;
                    case 0b000: wbData <= take  <7, 0> (loadData()); break;
                    case 0b001: wbData <= take <15, 0> (loadData()); break;
                    case 0b010: wbData <= take <31, 0> (loadData()); break;
                    case 0b100: wbData <= sign_extend  <7> (loadData()); break;
                    case 0b101: wbData <= sign_extend <15> (loadData()); break;
                }
            }
        }
    }
}

void writer::work_idle() {
    switch(take <ALU_type::width - 1, 0> (wrType())) {
        default: assert(false, "I give up..."); break;
        case ALU_type::scalar:      // Fallthrough.
        case ALU_type::pcImm:       // Fallthrough.
        case ALU_type::immediate:
            brDone  <= 0;
            wbDone  <= wbRd();
            wbData  <= scalarOut();
            details("-- Scalar writeback:", wbData.next(), "to", wbRd());
            break;

        case ALU_type::jalr:
            brDone  <= 1;
            brData  <= scalarOut();
            wbDone  <= wbRd();
            wbData  <= wbPc() + 4;
            details("-- Jalr writeback:", wbData.next(), "to", wbRd(),
                    " and jump to", int_to_hex(brData.next()));
            break;

        case ALU_type::branch:
            brDone  <= 1;
            brData  <= (scalarOut() ? wbPc() + wbImm() : wbPc() + 4);
            wbDone  <= 0;
            details("-- Branch PC: ", int_to_hex(brData.next()));
            break;

        case ALU_type::load:
            brDone  <= 0;
            wbDone  <= 0;
            status  <= LOAD;
            details("-- Loading data...");
            break;

        case ALU_type::store: // Do nothing.
            brDone  <= 0;
            wbDone  <= 0;
            details("-- Storing data...");
            break;
    }
}

} // namespace dark

