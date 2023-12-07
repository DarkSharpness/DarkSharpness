#pragma once
#include "utility.h"

namespace dark {


struct memctrl {
    static constexpr int IDLE   = 0;
    static constexpr int IFETCH = 1;
    static constexpr int READ   = 2;
    static constexpr int WRITE  = 3;

    wire mem_in;
    wire io_buffer_full;

    wire iFetchOn;  // Whether to fetch.
    wire iFetchPc;  // Ifetch PC.

    wire lsbType;   // 00xxx: off, 10xxx: read, 11000: write || low 3 bits are type.
    wire lsbAddr;   // Address to read/write.
    wire lsbData;   // Data to write.

    wire rollback;  // Roll back when branch mispredict.

  public:
    reg mem_out;    // Output to memory.
    reg mem_addr;   // Address to read/write.
    reg mem_wr;     // Whether to write.

    reg iDone;      // Whether the ifetch is done.
    reg lsbDone;    // Whether it's ok to stop

    reg loadData;   // Data loaded.

  private:
    reg status;
    reg bias;
    reg lens; // Length of read/write.

  public:
    void init(std::vector <wire> vec) {
        mem_in          = vec[0];
        io_buffer_full  = vec[1];
        iFetchOn        = vec[2];
        iFetchPc        = vec[3];
        lsbType         = vec[4];
        lsbAddr         = vec[5];
        lsbData         = vec[6];
        rollback        = vec[7];
    }

    void work() {
        if (reset || ~ready) {
            mem_wr  <= 0;
            iDone   <= 0;
            lsbDone <= 0;
            if (ready) status <= IDLE;
        } else {
            switch (status.value) {
                default: throw std::runtime_error("Invalid status");
                case IDLE:
                    // Speed up simulation using temporary variables.
                    if (int __lsbType = lsbType(); take <4> (__lsbType)) { // LSB enabled
                        // Set the operation length.
                        switch (take <1,0> (__lsbType)) {
                            default: throw std::runtime_error("Invalid lsbType");
                            case 0: lens <= 0; break;
                            case 1: lens <= 1; break;
                            case 2: lens <= 3; break;
                        }

                        status   <= take <4,3> (__lsbType);
                        bias     <= 0;
                        mem_addr <= lsbAddr();
                    } else if (iFetchOn()) {
                        status   <= IFETCH;
                        bias     <= 0;
                        lens     <= 3;
                        mem_addr <= iFetchPc();
                    } break;

                case IFETCH: // Almost the same.
                case READ:
                    // Wrong predict: Halt wrong reading.
                    if (rollback()) { status <= IDLE; break; }

                    switch (bias()) {
                        default: throw std::runtime_error("Invalid bias 1");
                        case 0: loadData.set_byte <0> (mem_in()); break;
                        case 1: loadData.set_byte <1> (mem_in()); break;
                        case 2: loadData.set_byte <2> (mem_in()); break;
                        case 3: loadData.set_byte <3> (mem_in()); break;
                    }

                    bias     <= bias() + 1;
                    mem_addr <= mem_addr() + 1;

                    if (bias() == lens()) {
                        iDone   <= (status() == IFETCH);
                        lsbDone <= (status() != IFETCH);
                        iDone   <= 1;
                        status  <= IDLE; 
                    } break;

                case WRITE:
                    if (io_buffer_full()) break; // Do nothing if the buffer is full.

                    switch (bias()) {
                        default: throw std::runtime_error("Invalid bias 2");
                        case 0: mem_out.set_byte <0> (lsbData()); break;
                        case 1: mem_out.set_byte <1> (lsbData()); break;
                        case 2: mem_out.set_byte <2> (lsbData()); break;
                        case 3: mem_out.set_byte <3> (lsbData()); break;
                    }

                    mem_wr <= 1;
                    bias   <= bias() + 1;
                    if (bias()) mem_addr <= mem_addr() + 1;

                    if (bias() == lens()) {
                        lsbDone <= 1;
                        status  <= IDLE;
                    } break;
            }
        }
    }

    void sync() {
        bias.sync();
        status.sync();
        mem_out.sync();
        mem_addr.sync();
        mem_wr.sync();
        iDone.sync();
        lsbDone.sync();
        loadData.sync();
    }
}; // struct memctrl



} // namespace dark
