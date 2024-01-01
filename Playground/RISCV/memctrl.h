#pragma once
#include "utility.h"

namespace dark {

struct memctrl_input {
    wire mem_in;
    wire io_buffer_full;

    wire iFetchOn;  // Whether to fetch.
    wire iFetchPc;  // Ifetch PC.

    wire memType;           // For read/write.
    wire memSize;           // Memory length.
    wire memAddr;           // Address from decoder.
    wire scalarStore;       // Data to write.

    // wire stride;    // Stride if vector.
};

struct memctrl_output {
    reg  mem_out;   // Output to memory.
    reg  mem_addr;  // Address to read/write.
    reg  mem_wr;    // Whether to write.

    reg  iDone;     // Whether the ifetch is done.
    reg  memDone;   // Whether it's ok to stop

    reg  status;        // Status of the execution.
    reg  scalarLoad;    // Data loaded
};

struct memctrl_private {
    reg stage;      // Stage of the execution.
    reg lens;       // Length of read/write.
};

struct memctrl : memctrl_input, memctrl_output, memctrl_private {
    using sync = sync_tag <memctrl_output, memctrl_private>;
    friend class caster <memctrl_private>;

    static constexpr int IDLE           = 0;
    static constexpr int IFETCH         = 1;
    static constexpr int SCALAR_READ    = 2;
    static constexpr int SCALAR_WRITE   = 3;
    static constexpr int VECTOR_READ    = 6;
    static constexpr int VECTOR_WRITE   = 7;

    void work();

  private:
    void dbg_print_load() const {
        if (status() == IFETCH) {
            details("= Instruction loaded :" , int_to_hex(scalarLoad.next()) ,
                    " at " , int_to_hex(mem_addr()));
        } else {
            details("= Data loaded :" , int_to_hex(scalarLoad.next()) ,
                    " at " , mem_addr() - lens() + 1,
                    ", length ", lens());
        }
    }

    void dbg_print_store() const {
        details("Data stored :" , int_to_hex(scalarStore()),
                            " at " , mem_addr() - lens() + 2,
                            ", length ", lens());
    }
};

} // namespace dark


namespace dark {

void memctrl::work() {
    if (reset) {
        mem_wr  <= 0;
        iDone   <= 0;
        memDone <= 0;
        status  <= IDLE;
    } if (!ready) {
        mem_wr  <= 0; // Only disable write.
    } else {
        switch (status()) {
            default: assert(false); break;
            case IDLE:
                if (memType()) {
                    stage    <= 0;
                    lens     <= memSize();
                    status   <= memType();
                    mem_addr <= memAddr();
                    mem_out  <= scalarStore();
                } else if (iFetchOn()) {
                    stage    <= 0;
                    lens     <= 4;
                    status   <= IFETCH;
                    mem_addr <= iFetchPc();
                }
                iDone    <= 0; // Reset the signal.
                mem_wr   <= 0; // Reset the signal.
                memDone  <= 0; // Reset the signal.
                break;

            case IFETCH: // Fall through.
            case SCALAR_READ:
                stage <= stage() + 1;
                switch (stage()) {
                    default: assert(false); break;
                    case 0: break;  // Wait for the data to come.
                    case 1:         // All done.
                        status      <= IDLE;
                        iDone       <= (status() == IFETCH);
                        memDone     <= (status() != IFETCH);
                        scalarLoad  <= mem_in();
                        dbg_print_load();
                } break;

            case SCALAR_WRITE:
                if (io_buffer_full()) break; // Do nothing if the buffer is full.
                switch (stage()) {
                    default: assert(false); break;
                    case 0: // Write to memory.
                        status  <= IDLE;
                        memDone <= 1;
                        mem_wr  <= lens();
                        dbg_print_store();
                } break;

            case VECTOR_READ:
            case VECTOR_WRITE:
                NotImplemented();
        }
    }
}

} // namespace dark
