#pragma once
#include "utility.h"

namespace dark {

struct memctrl_input {
    wire mem_in;
    wire io_buffer_full;

    wire iFetchOn;  // Whether to fetch.
    wire iFetchPc;  // Ifetch PC.

    wire lsbType;           // low 2 bits are avail and read/write.
    wire lsbAddr;           // Address to read/write.
    wire lsbData[VIDX];     // Data to write.

    // wire rollback;  // Roll back when branch mispredict.
};

struct memctrl_output {
    using regs = std::array <reg, VIDX>;

    reg  mem_out;   // Output to memory.
    reg  mem_addr;  // Address to read/write.
    reg  mem_wr;    // Whether to write.

    reg  iDone;     // Whether the ifetch is done.
    reg  lsbDone;   // Whether it's ok to stop

    regs loadData;  // Data loaded.
};

struct memctrl_private {
    reg  status; // Status of the execution.
    reg  stage;  // Stage of the execution.
    reg  lens;   // Length of read/write.
    reg  toWrite[VIDX]; // Data to write.
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
        loadData[N / 4].set_byte <N % 4> (mem_in());
    }

    template <size_t N>
    void set_stored() {
        static_assert (N < VIDX * 4);
        constexpr auto pos = (N % 4) * 8;
        mem_out <= take <pos + 7, pos> (lsbData[N / 4]());
    }
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
                if (int __lsbType = lsbType(); take <1> (__lsbType)) { // LSB enabled
                    lens     <= take <31,2> (__lsbType);
                    status   <= take <1, 0> (__lsbType);
                    stage    <= 0;
                    mem_addr <= lsbAddr();

                } else if (iFetchOn()) {
                    lens     <= 4;
                    status   <= IFETCH;
                    stage    <= 0;
                    mem_addr <= iFetchPc();
                } break;

            case IFETCH: // Fall through.
            case READ:
                // Wrong predict: Halt wrong reading (?)
                // if (rollback())  { status <= IDLE; break; }

                switch (stage()) {
                    default: assert(false);
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
                if (stage() != 0) { mem_addr <= mem_addr() + 1; }
                if (stage() + 1 == lens()) {
                    lsbDone <= 1;
                    status  <= IDLE;
                }
        }
    }
}

} // namespace dark
