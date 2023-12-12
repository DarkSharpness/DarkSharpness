#pragma once
#include "utility.h"

namespace dark {

struct memctrl_input {
    wire mem_in;
    wire io_buffer_full;

    wire iFetchOn;  // Whether to fetch.
    wire iFetchPc;  // Ifetch PC.

    wire lsbType;   // 00xxx: off, 10xxx: read, 11000: write || low 3 bits are type.
    wire lsbAddr;   // Address to read/write.
    wire lsbData;   // Data to write.

    wire rollback;  // Roll back when branch mispredict.
};

struct memctrl_output {
    reg  mem_out;   // Output to memory.
    reg  mem_addr;  // Address to read/write.
    reg  mem_wr;    // Whether to write.

    reg  iDone;     // Whether the ifetch is done.
    reg  lsbDone;   // Whether it's ok to stop

    reg  loadData;  // Data loaded.
};

struct memctrl_private {
    reg status; // Status of the execution.
    reg stage;  // Stage of the execution.
    reg lens;   // Length of read/write.
};

struct memctrl : memctrl_input, memctrl_output, memctrl_private {
    using sync = sync_tag <memctrl_output, memctrl_private>;

    friend class caster <memctrl_private>;
    static constexpr int IDLE   = 0;
    static constexpr int IFETCH = 1;
    static constexpr int READ   = 2;
    static constexpr int WRITE  = 3;
    void work();
};

} // namespace dark


namespace dark {


void memctrl::work() {
    if (reset) {
        mem_wr  <= 0;
        iDone   <= 0;
        lsbDone <= 0;
        status  <= IDLE;
    } if (!ready) {
        mem_wr  <= 0;
    } else {
        switch (status()) {
            default: assert(false); break;
            case IDLE:
                // Speed up simulation using temporary variables.
                if (int __lsbType = lsbType(); take <4> (__lsbType)) { // LSB enabled
                    // Set the operation length.
                    switch (take <1,0> (__lsbType)) {
                        default: assert(false); break;
                        case 0: lens <= 1; break;
                        case 1: lens <= 2; break;
                        case 2: lens <= 4; break;
                    }
                    status   <= take <4,3> (__lsbType);
                    stage    <= 0;
                    mem_addr <= lsbAddr();
                } else if (iFetchOn()) {
                    lens     <= 4;
                    status   <= IFETCH;
                    stage    <= 0;
                    mem_addr <= iFetchPc();
                } break;

            case IFETCH:
            case READ:
                // Wrong predict: Halt wrong reading.
                if (rollback())  { status <= IDLE; break; }

                switch (stage()) {
                    default: assert(false);
                    case 0: break; // Wait for the data to come.
                    case 1: loadData.set_byte <0> (mem_in()); break;
                    case 2: loadData.set_byte <1> (mem_in()); break;
                    case 3: loadData.set_byte <2> (mem_in()); break;
                    case 4: loadData.set_byte <3> (mem_in()); break;
                }

                stage    <= stage() + 1;
                mem_addr <= mem_addr() + 1;

                if (stage() == lens()) {
                    iDone   <= (status() == IFETCH);
                    lsbDone <= (status() != IFETCH);
                    iDone   <= 1;
                    status  <= IDLE; 
                } break;

            case WRITE:
                if (io_buffer_full()) break; // Do nothing if the buffer is full.

                switch (stage()) {
                    default: assert(false); break;
                    case 0: mem_out <= take <7 , 0> (lsbData()); break;  
                    case 1: mem_out <= take <15, 8> (lsbData()); break;
                    case 2: mem_out <= take <23,16> (lsbData()); break;
                    case 3: mem_out <= take <31,24> (lsbData()); break;
                }

                mem_wr <= 1;
                stage  <= stage() + 1;
                if (stage() != 0) mem_addr <= mem_addr() + 1;

                if (stage() + 1 == lens()) {
                    lsbDone <= 1;
                    status  <= IDLE;
                } break;
        }
    }
}


} // namespace dark
