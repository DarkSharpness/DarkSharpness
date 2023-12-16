#pragma once
#include "utility.h"

namespace dark {

struct memctrl_input {
    wire mem_in;
    wire io_buffer_full;

    wire iFetchOn;  // Whether to fetch.
    wire iFetchPc;  // Ifetch PC.

    wire memType;           // low 2 bits are avail and read/write.
    wire memAddr;           // Address from decoder.
    vwire memData;          // Data to write.

    // wire stride;    // Stride if vector.
};

struct memctrl_output {
    reg  mem_out;   // Output to memory.
    reg  mem_addr;  // Address to read/write.
    reg  mem_wr;    // Whether to write.

    reg  iDone;     // Whether the ifetch is done.
    reg  memDone;   // Whether it's ok to stop

    reg  status;    // Status of the execution.

    vreg loadData;  // Data loaded.
};

struct memctrl_private {
    reg stage;      // Stage of the execution.
    reg lens;       // Length of read/write.
    // reg bias;   // Bias of each memory stride.
};

struct memctrl : memctrl_input, memctrl_output, memctrl_private {
    using sync = sync_tag <memctrl_output, memctrl_private>;

    friend class caster <memctrl_private>;
    static constexpr int IDLE   = 0;
    static constexpr int IFETCH = 1;
    static constexpr int READ   = 2;
    static constexpr int WRITE  = 3;
    void work();

  private:
    template <size_t N>
    void set_loaded() {
        static_assert (N < VIDX * 4);
        loadData[N / 4].set_byte(N % 4,mem_in());
    }

    template <size_t N>
    void set_stored() {
        static_assert (N < VIDX * 4);
        constexpr auto pos = (N % 4) * 8;
        mem_out <= take <pos + 7, pos> (memData[N / 4]());
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
                // Speed up simulation using temporary variables.
                if (int __memType = memType(); take <1> (__memType)) {
                    lens     <= take <31,2> (__memType);
                    status   <= take <1, 0> (__memType);

                    stage    <= 0;
                    mem_addr <= memAddr();
                    details("Memory address: ", memAddr());
                    // bias     <= stride();
                } else if (iFetchOn()) {
                    lens     <= 4;
                    status   <= IFETCH;

                    stage    <= 0;
                    mem_addr <= iFetchPc();
                    // bias     <= 1;
                }
                mem_wr  <= 0; // Reset the signal.
                iDone   <= 0; // Reset the signal.
                memDone <= 0; // Reset the signal.
                break;

            case IFETCH: // Fall through.
            case READ:

                switch (stage()) {
                    default: assert(false); break;
                    case 0: break; // Wait for the data to come.
                    case 1: set_loaded <0> (); break;
                    case 2: set_loaded <1> (); break;
                    case 3: set_loaded <2> (); break;
                    case 4: set_loaded <3> (); break;
                    case 5: set_loaded <4> (); break;
                    case 6: set_loaded <5> (); break;
                    case 7: set_loaded <6> (); break;
                    case 8: set_loaded <7> (); break;
                }

                stage    <= stage() + 1;
                if (stage() + 1 < lens())
                    mem_addr <= mem_addr() + 1; // bias();

                if (stage() == lens()) {
                    iDone   <= (status() == IFETCH);
                    memDone <= (status() != IFETCH);
                    status  <= IDLE;

                    loadData[0].sync(); // In order to see the result...

                    if (status() == IFETCH) {
                        details("= Instruction loaded :" , int_to_hex(loadData[0]()) ,
                                " at " , int_to_hex(mem_addr() - 4));
                    } else {
                        details("= Data loaded :" , int_to_hex(loadData[0]()) ,
                                " at " , mem_addr() - lens() + 1,
                                ", length ", lens());
                    }
                } break;

            case WRITE:
                if (io_buffer_full()) break; // Do nothing if the buffer is full.

                switch (stage()) {
                    default: assert(false); break;
                    case 0: set_stored <0> (); break;
                    case 1: set_stored <1> (); break;
                    case 2: set_stored <2> (); break;
                    case 3: set_stored <3> (); break;
                    case 4: set_stored <4> (); break;
                    case 5: set_stored <5> (); break;
                    case 6: set_stored <6> (); break;
                    case 7: set_stored <7> (); break;
                }

                mem_wr <= 1;
                stage  <= stage() + 1;
                if (stage() != 0) mem_addr <= mem_addr() + 1; // bias();
                if (stage() + 1 == lens()) {
                    memDone <= 1;
                    status  <= IDLE;
                    details("Data stored :" , int_to_hex(memData[0]()),
                            " at " , mem_addr() - lens() + 2,
                            ", length ", lens());
                }
        }
    }
}

} // namespace dark
