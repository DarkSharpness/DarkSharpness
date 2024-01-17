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
    wire memData;           // Data to write.

    vwire vecData;          // Vector data to write.
    vwire vecAddr;          // Vector address to read/write.

    wire stride;            // Offset of elements.
};

struct memctrl_output {
    reg  mem_out;   // Output to memory.
    reg  mem_addr;  // Address to read/write.
    reg  mem_wr;    // Whether to write.

    reg  iDone;     // Whether the ifetch is done.
    reg  memDone;   // Whether it's ok to stop

    reg  scalarLoad;    // Data loaded
    vreg vectorLoad;    // Vector loaded
};

struct memctrl_private {
    reg status;     // Status of the execution.
    reg stage;      // Stage of the execution.
    reg lens;       // Length of read/write.
    reg dist;       // Distance of each element.
};

struct memctrl : public memctrl_input, memctrl_output, private memctrl_private {
    using sync = sync_tag <memctrl_output, memctrl_private>;
    friend class caster <memctrl>;

    const wire memStatus = status;

    static constexpr int IDLE           = 0;
    static constexpr int IFETCH         = 1;
    static constexpr int SCALAR_READ    = 2;
    static constexpr int SCALAR_WRITE   = 3;
    static constexpr int VECTOR_READ    = 4;    // Stride mode.
    static constexpr int VECTOR_WRITE   = 5;    // Stride mode.
    static constexpr int VECTOR_READ_2  = 6;    // Address mode.
    static constexpr int VECTOR_WRITE_2 = 7;    // Address mode.

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
        details("= Data stored :" , int_to_hex(memData()),
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
                    mem_out  <= memData();
                    dist     <= stride();
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
                static_assert(VIDX == 2, "Only support vector of size 2.");
                stage <= stage() + 1;
                if (lens() == 4) {
                    if (stage() < 1)
                        mem_addr <= mem_addr() + dist();
                    switch (stage()) {
                        default: assert(false); break;
                        case 0: break;
                        case 1: vectorLoad[0] <= mem_in(); break;
                        case 2: vectorLoad[1] <= mem_in(); break;
                    }
                    if (stage() == 2) {
                        status  <= IDLE;
                        memDone <= 1;
                    }
                } else if (lens() == 2) {
                    if (stage() < 3)
                        mem_addr <= mem_addr() + dist();
                    switch (stage()) {
                        default: assert(false); break;
                        case 0: break;
                        case 1: vectorLoad[0].set_half(0, mem_in()); break;
                        case 2: vectorLoad[0].set_half(1, mem_in()); break;
                        case 3: vectorLoad[1].set_half(0, mem_in()); break;
                        case 4: vectorLoad[1].set_half(1, mem_in()); break;
                    }
                    if (stage() == 4) {
                        status  <= IDLE;
                        memDone <= 1;
                    }
                } else if (lens() == 4) {
                    if (stage() < 7)
                        mem_addr <= mem_addr() + dist();
                    switch (stage()) {
                        default: assert(false); break;
                        case 0: break;
                        case 1: vectorLoad[0].set_byte(0, mem_in()); break;
                        case 2: vectorLoad[0].set_byte(1, mem_in()); break;
                        case 3: vectorLoad[0].set_byte(2, mem_in()); break;
                        case 4: vectorLoad[0].set_byte(3, mem_in()); break;
                        case 5: vectorLoad[1].set_byte(0, mem_in()); break;
                        case 6: vectorLoad[1].set_byte(1, mem_in()); break;
                        case 7: vectorLoad[1].set_byte(2, mem_in()); break;
                        case 8: vectorLoad[1].set_byte(3, mem_in()); break;
                    }
                }

            case VECTOR_WRITE:
                static_assert(VIDX == 2, "Only support vector of size 2.");
                if (io_buffer_full()) break; // Do nothing if the buffer is full.

                stage <= stage() + 1;
                if (stage() != 0)
                    mem_addr <= mem_addr() + dist();
                mem_wr <= lens();

                if (lens() == 4) {
                    switch (stage()) {
                        default: assert(false); break;
                        case 0:
                            mem_out <= vecData[0](); break;
                        case 1:
                            mem_out <= vecData[1](); break;
                    }
                    if (stage() == 1) {
                        status  <= IDLE;
                        memDone <= 1;
                    }
                } else if (lens() == 2) {
                    switch (stage()) {
                        default: assert(false); break;
                        case 0:
                            mem_out <= take <15,0>  (vecData[0]());  break;
                        case 1:
                            mem_out <= take <31,16> (vecData[0]()); break;
                        case 2:
                            mem_out <= take <15,0>  (vecData[1]());  break;
                        case 3:
                            mem_out <= take <31,16> (vecData[1]()); break;
                    }
                    if (stage() == 3) {
                        status  <= IDLE;
                        memDone <= 1;
                    }
                } else if (lens() == 1) {
                    switch (stage()) {
                        default: assert(false); break;
                        case 0:
                            mem_out <= take <7,0>   (vecData[0]()); break;
                        case 1:
                            mem_out <= take <15,8>  (vecData[0]()); break;
                        case 2:
                            mem_out <= take <23,16> (vecData[0]()); break;
                        case 3:
                            mem_out <= take <31,24> (vecData[0]()); break;
                        case 4:
                            mem_out <= take <7,0>   (vecData[1]()); break;
                        case 5:
                            mem_out <= take <15,8>  (vecData[1]()); break;
                        case 6:
                            mem_out <= take <23,16> (vecData[1]()); break;
                        case 7:
                            mem_out <= take <31,24> (vecData[1]()); break;
                    }
                    if (stage() == 7) {
                        status  <= IDLE;
                        memDone <= 1;
                    }
                } break;
        }
    }
}

} // namespace dark
