#pragma once
#include "utility.h"
#include "register.h"

namespace dark {

struct decoder_input {
    wire insDone;   // Whether the instruction is available.
    wire insData;   // Instruction to decode.
    wire insPc;     // Instruction PC.
    wire memInput;  // Data from memory.
};

struct decoder_output {
    using regs = std::array <reg, VIDX>;

    reg  issue;     // Whether to issue.
    reg  itype;     // 0 if normal.
                    // 1 if branch.
                    // 2 if jalr.
                    // 3 if vector.
                    // 4 if load/store

    reg  rs1Data;   // Data if scalar. Index if vector.
    reg  rs2Data;   // Data if scalar. Index if vector.

    reg  rdIndex;   // Index in register file.
    reg  opType;    // Operation type (decoded).

    reg  memType;   // To memctrl.
    reg  memAddr;   // To memctrl.
    regs memData;   // To memory.
};

struct instruction_queue {
    static constexpr int width  = 4;
    static constexpr int lines  = 1 << width;

    struct reg2 {
        reg ins; reg pc;
        struct pair { int x,y; };
        void sync() { ins.sync(); pc.sync(); }
        void operator <= (pair n) { ins <= n.x; pc <= n.y; }
    };

    std::array <reg2, lines> queue;

    reg head;
    reg tail;

    static int round(int val) { return val & (lines - 1); }
    int size() const { return round(tail() - head()); }
    bool avail() const { return size() < lines - 2; }
    bool empty() const { return head() == tail(); }
};


struct decoder : public decoder_input, decoder_output, private instruction_queue, register_file {
    using sync = sync_tag <decoder_output, instruction_queue, register_file>;
    friend class caster <decoder>;
    void work();

  private:
 
    static int rd(int ins)  { return take <11,7> (ins);  }
    static int rs1(int ins) { return take <19,15> (ins); }
    static int rs2(int ins) { return take <24,20> (ins); }
    static int jalrImm(int ins) { return sign_extend(take <31,20> (ins)); }
    static int funct3(int ins) { return take <14,12> (ins); }
};

} // namespace dark

namespace dark {

void decoder::work() {
    // Decoder part.
    if (reset) {
        issue   <= 0;
    } else if (ready && !empty()) {
        int __ins = queue[head()].ins();
        switch (take <6,0> (__ins)) {
            case 0b1101111: // jal
                dirty[rd(__ins)] <= 1;
                rdIndex <= rd(__ins);
                rs1Data <= insPc();
                rs2Data <= 4;
                opType  <= (int)(ALUop::ADD);

                issue   <= 1;
                itype   <= 0;
                head    <= round(head() + 1);
                break;

            case 0b1100111: // jalr
                if (dirty[rs1(__ins)]() || dirty[rd(__ins)]()) break;
                dirty[rd(__ins)] <= 1;
                rdIndex <= rd(__ins);
                rs1Data <= rs1(__ins);
                rs2Data <= jalrImm(__ins);
                opType  <= (int)(ALUop::ADD);

                issue   <= 1;
                itype   <= 2;
                head    <= round(head() + 1);
                break;

            case 0b1100011: // branch
                if (dirty[rs1(__ins)]() || dirty[rs2(__ins)]()) break;
                dirty[rd(__ins)] <= 1;
                rdIndex <= rd(__ins);
                rs1Data <= rs1(__ins);
                rs2Data <= rs2(__ins);

                issue   <= 1;
                itype   <= 1;
                head    <= round(head() + 1);

                switch (funct3(__ins)) {
                    default: assert(false); break;
                    case 0b000: // beq
                        opType <= (int)(ALUop::SEQ);
                        break;
                    case 0b001: // bne
                        opType <= (int)(ALUop::SNEQ);
                        break;
                    case 0b100: // blt
                        opType <= (int)(ALUop::SLT);
                        break;
                    case 0b101: // bge
                        opType <= (int)(ALUop::SGE);
                        break;
                    case 0b110: // bltu
                        opType <= (int)(ALUop::SLTU);
                        break;
                    case 0b111: // bgeu
                        opType <= (int)(ALUop::SGEU);
                        break;
                }       break;

            case 0b0000011: // load
                if (dirty[rs1(__ins)]() || dirty[rd(__ins)]()) break;
                dirty[rd(__ins)] <= 1;
                rdIndex <= rd(__ins);
                rs1Data <= rs1(__ins);
                rs2Data <= sign_extend(take <31,20> (__ins));
                opType  <= (int)(ALUop::ADD);

                issue   <= 1;
                itype   <= 4;
                head    <= round(head() + 1);
                break;

            case 0b0100011: // store
                if (dirty[rs1(__ins)]() || dirty[rs2(__ins)]()) break;
                rs1Data <= rs1(__ins);
                rs2Data <= rs2(__ins);
                opType  <= (int)(ALUop::ADD);

                issue   <= 1;
                itype   <= 4;
                head    <= round(head() + 1);
                break;

        }
    }

    // Ins queue part.
    if (reset) {
        head    <= 0;
        tail    <= 0;
    } else if (ready && insDone()) {
        tail    <= round(tail() + 1);
        queue[tail()] <= reg2::pair {insData(), insPc()};
    }
}

} // namespace dark
