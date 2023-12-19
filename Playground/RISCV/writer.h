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
    wire memStatus;     // Status of the memory.
    wire loadData;      // Data loaded.

    wire    scalarData; // Scalar data from register file (for storing)
    vwire   vectorData; // Vector data from register file (for storing)

    wire    dbgCmd;    // Debug command.
};

struct writer_output {
    reg  brDone;        // Whether a branch/jalr is just done.
    reg  brData;        // The new PC of a branch/jalr destination.

    reg  wbDone;        // Whether a writeback is just done.
    reg  wbData;        // The data to write back to register file.

    reg  memType;       // Memory type.
    reg  memAddr;       // Memory address.
    reg  scalarStore;   // Memory data to store.
};

struct writer_private {
    reg status; // Status of the execution.
    reg curType;// Current type of wrType.
};

struct writer : public writer_input, writer_output, private writer_private {
    using sync = sync_tag <writer_output, writer_private>;
    friend class caster <writer>;

    void work();

  private:
    static constexpr int IDLE = 0, LOAD = 1, STORE = 2;
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
        switch (status()) {
            default: assert(false, "It's already enough... Fxxk you!"); break;
            case IDLE:
                if (wrWork()) {
                    details("-- Writeback PC:", int_to_hex(wbPc()));
                    work_idle();
                } else {
                    brDone <= 0;
                    wbDone <= 0;
                } break;

            case LOAD:
                // If Scalar READ/WRITE is operating, reset memType.
                if (take <1> (memStatus()))
                    memType <= 0; // Stop the query if reading/writing.
                if (memDone()) {
                    status <= IDLE;
                    wbDone <= wbRd();
                    switch (ALU_type::funct3(curType())) {
                        default: assert(false, "I give up..."); break;
                        case 0b000: wbData <= take  <7, 0> (loadData()); break;
                        case 0b001: wbData <= take <15, 0> (loadData()); break;
                        case 0b010: wbData <= take <31, 0> (loadData()); break;
                        case 0b100: wbData <= sign_extend  <7> (loadData()); break;
                        case 0b101: wbData <= sign_extend <15> (loadData()); break;
                    }
                    details("-- Load from", int_to_hex(memAddr()), "to", wbRd(), ":", wbData.next());
                } break;

            case STORE:
                if (take <1> (memStatus()))
                    memType <= 0; // Stop the query if reading/writing.
                if (memDone()) {
                    status  <= IDLE;
                    details("-- Store to", int_to_hex(memAddr()), ":", scalarData());
                }
                break;
        }
    }
}

void writer::work_idle() {
    switch(take <ALU_type::width - 1, 0> (wrType())) {
        default: assert(false, "I give up..."); break;
        case ALU_type::scalar:
        case ALU_type::pcImm:
        case ALU_type::immediate:
            brDone  <= 0;
            wbDone  <= wbRd();
            wbData  <= scalarOut();
            memType <= 0;
            details("-- Scalar writeback:", wbData.next(), "to", wbRd());
            break;

        case ALU_type::jalr:
            brDone  <= 1;
            brData  <= scalarOut();
            wbDone  <= wbRd();
            wbData  <= wbPc() + 4;
            memType <= 0;
            details("-- Jalr writeback:", wbData.next(), "to", wbRd(),
                    " and jump to", int_to_hex(brData.next()));
            break;

        case ALU_type::branch:
            brDone  <= 1;
            brData  <= (scalarOut() ? wbPc() + wbImm() : wbPc() + 4);
            wbDone  <= 0;
            memType <= 0;
            details("-- Branch PC: ", int_to_hex(brData.next()));
            break;

        case ALU_type::load:
            brDone  <= 0;
            wbDone  <= 0;
            status  <= LOAD;
            memAddr <= scalarOut();
            curType <= wrType();
            if (memAddr() == 131036) {
                details("?");
            }
            switch (ALU_type::funct3_2(wrType())) {
                default: assert(false, "I give up..."); break;
                case 0b00: memType <= 0b00110; break;
                case 0b01: memType <= 0b01010; break;
                case 0b10: memType <= 0b10010; break;
            }
            break;

        case ALU_type::store:
            brDone      <= 0;
            wbDone      <= 0;
            status      <= STORE;
            memAddr     <= scalarOut();
            curType     <= wrType();
            scalarStore <= scalarData();
            switch (ALU_type::funct3_2(wrType())) {
                default: assert(false, "I give up..."); break;
                case 0b00: memType <= 0b00111; break;
                case 0b01: memType <= 0b01011; break;
                case 0b10: memType <= 0b10011; break;
            }
            break;

        case ALU_type::vector:
            assert(false, "Vector is not supported yet.");
            break;
    }
}

} // namespace dark

