#pragma once
#include "utility.h"

namespace dark {

struct decoder_input {
    wire insDone;   // Whether the instruction is available.
    wire insData;   // Instruction to decode.
    wire insPc;     // Instruction PC.
};

struct decoder_output {
    reg  issue;     // Whether to issue + vector/scalar.

    reg  rs1Data;   // Data if scalar. Index if vector.
    reg  rs2Data;   // Data if scalar. Index if vector.

    reg  rdIndex;   // Index in register file.
    reg  opType;    // Operation type (decoded).
};

struct instruction_queue {
    static constexpr int width  = 4;
    static constexpr int lines  = 1 << width;
    std::array <reg, lines> queue;

    reg head;
    reg tail;

    static int round(int val) { return val & (lines - 1); }
    int size() const { return round(tail() - head()); }
    bool avail() const { return size() < lines - 2; }
    bool empty() const { return head() == tail(); }
};


struct decoder : public decoder_input, decoder_output, private instruction_queue {
    using sync = sync_tag <decoder_output, instruction_queue>;
    friend class caster <decoder>;
    void work();
};

} // namespace dark

namespace dark {

void decoder::work() {
    if (reset) {
        issue   <= 0;
    } else if (ready && !empty()) {


    }

    if (reset) {
        head    <= 0;
        tail    <= 0;
    } else if (ready && insDone()) {
        tail    <= round(tail() + 1);
        queue[tail()] <= insData();
    }
}

} // namespace dark
