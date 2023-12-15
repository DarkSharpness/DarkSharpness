#pragma once
#include "utility.h"
#include "register.h"

namespace dark {

struct decoder_input {
    wire insDone;   // Whether the instruction is fetched.
    wire insData;   // Instruction to decode.
    wire insPc;     // Instruction PC.

    wire rs1Busy;   // Whether rs1 is busy.
    wire rs2Busy;   // Whether rs2 is busy.
    wire rdBusy;    // Whether rd is busy.

    wire vs1Busy;   // Whether vs1 is busy.
    wire vs2Busy;   // Whether vs2 is busy.
    wire vdBusy;    // Whether vd is busy.

    wire nextBubble;    // Whether to bubble (if load/store)
};

struct decoder_output {
    reg  issue;     // Whether to issue.
    reg  iType;     // Instruction type for ALU.
    reg  ALUPc;     // Pc for ALU.
    reg  rs1Index;  // Index for rs1.
    reg  rs2Index;  // Index for rs2.
    reg  rdIndex;   // Index in register file.
    reg  immediate; // Immediate value.
    reg  opType;    // Operation type for ALU.
};

struct ins_queue {
    static constexpr int width  = 4;
    static constexpr int lines  = 1 << width;
    struct entry {
        reg ins, pc;
        void sync() { ins.sync(); pc.sync(); }
    };
    std::array <entry, lines> queue;
    reg head, tail;

  protected:
    static int round(int val) { return val & (lines - 1); }
    int  size()  const { return round(tail() - head()); }
    bool avail() const { return size() < lines - 2; }
    bool empty() const { return head() == tail(); }
};


struct decoder : public decoder_input, decoder_output, private ins_queue {
    using sync = sync_tag <decoder_output, ins_queue>;
    friend class caster <decoder>;
    void work();

    const wire rs1Head = { [this] () -> int { return rs1(queue[head()].ins()); } };
    const wire rs2Head = { [this] () -> int { return rs2(queue[head()].ins()); } };
    const wire rdHead  = { [this] () -> int { return rd (queue[head()].ins()); } };
    const wire notFull = { [this] () -> int { return avail(); } };

  private:

    static int rd(int ins)  { return take <11,7> (ins);  }
    static int rs1(int ins) { return take <19,15> (ins); }
    static int rs2(int ins) { return take <24,20> (ins); }
    static int jalrImm(int ins) { return sign_extend(take <31,20> (ins)); }
    static int funct3(int ins)  { return take <14,12> (ins); }
    static int loadImm(int ins) { return sign_extend(take <31,20> (ins)); }
    static int storeImm(int ins){
        return sign_extend(bits {take <31,25> (ins), take <11,7> (ins)});
    }
    static int brImm(int ins) {
        return sign_extend(bits {
            take <31> (ins) , take <7> (ins) , take <30, 25> (ins), take <11,8> (ins) , bits <1> (0)
        });
    }

    void issue_fail() { issue <= 0; }
    void issue_success() {
        issue   <= 1;
        head    <= round(head() + 1);
    }

    void work_lui(int __ins) {
        if (rdBusy()) return issue_fail();
        issue_success();
        rs1Index    <= 0;       // Zero register.
        rs2Index    <= 0;       // Zero register.
        rdIndex     <= rd(__ins);
        immediate   <= bits {take <31,12> (__ins), bits <12> (0)};

        iType       <= ALU_type::immediate;
        opType      <= ALU_op::ADD;
    }

    void work_auipc(int __ins) {
        if (rdBusy()) return issue_fail();
        issue_success();

        rs1Index    <= 0;       // Zero register.
        rs2Index    <= 0;       // Zero register.
        rdIndex     <= rd(__ins);
        immediate   <= take <31,12> (__ins);

        iType       <= ALU_type::pcImm;
        opType      <= ALU_op::ADD;
    }

    void work_jal(int __ins) {
        if (rdBusy()) return issue_fail();
        issue_success();

        rs1Index    <= 0;       // Zero register.
        rs2Index    <= 0;       // Zero register.
        rdIndex     <= rd(__ins);
        immediate   <= 4;

        iType       <= ALU_type::pcImm;
        opType      <= ALU_op::ADD;
    }

    void work_jalr(int __ins) {
        if (rdBusy() || rs1Busy()) return issue_fail();
        issue_success();

        rs1Index    <= rs1(__ins);
        rs2Index    <= 0;       // Zero register.
        rdIndex     <= rd(__ins);
        immediate   <= jalrImm(__ins);

        iType       <= ALU_type::jalr;
        opType      <= ALU_op::ADD;
    }

    void work_branch(int __ins) {
        if (rs1Busy() || rs2Busy()) return issue_fail();
        issue_success();

        rs1Index    <= rs1(__ins);
        rs2Index    <= rs2(__ins); 
        rdIndex     <= 0;       // Zero register.
        immediate   <= brImm(__ins);

        iType       <= ALU_type::branch;
        switch (funct3(__ins)) {
            default: assert(false); break;
            case 0b000: // beq
                opType <= ALU_op::SEQ;
                break;
            case 0b001: // bne
                opType <= ALU_op::SNEQ;
                break;
            case 0b100: // blt
                opType <= ALU_op::SLT;
                break;
            case 0b101: // bge
                opType <= ALU_op::SGE;
                break;
            case 0b110: // bltu
                opType <= ALU_op::SLTU;
                break;
            case 0b111: // bgeu
                opType <= ALU_op::SGEU;
                break;
        }
    }

    void work_load(int __ins) {
        if (rdBusy() || rs1Busy()) return issue_fail();
        issue_success();

        rs1Index    <= rs1(__ins);
        rs2Index    <= 0;       // Zero register.
        rdIndex     <= rd(__ins);
        immediate   <= loadImm(__ins);

        constexpr auto __wid = ALU_type::width;

        iType       <= (funct3(__ins) << __wid | ALU_type::load);
        opType      <= ALU_op::ADD;
    }

    void work_store(int __ins) {
        if (rs1Busy() || rs2Busy()) return issue_fail();
        issue_success();

        rs1Index    <= rs1(__ins);
        rs2Index    <= rs2(__ins);
        rdIndex     <= 0;       // Zero register.
        immediate   <= storeImm(__ins);

        constexpr auto __wid = ALU_type::width;

        iType       <= (funct3(__ins) << __wid | ALU_type::store);
        opType      <= ALU_op::ADD;
    }

    void work_immediate(int __ins) {
        if (rdBusy() || rs1Busy()) return issue_fail();
        issue_success();

        rs1Index    <= rs1(__ins);
        rs2Index    <= 0;       // Zero register.
        rdIndex     <= rd(__ins);
        immediate   <= sign_extend(take <31,20> (__ins));

        iType       <= ALU_type::immediate;
        switch (funct3(__ins)) {
            default: assert(false); break;
            case 0b000: // addi
                opType <= ALU_op::ADD;  break;
            case 0b010: // slti
                opType <= ALU_op::SLT;  break;
            case 0b011: // sltiu
                opType <= ALU_op::SLTU; break;
            case 0b100: // xori
                opType <= ALU_op::XOR;  break;
            case 0b110: // ori
                opType <= ALU_op::OR;   break;
            case 0b111: // andi
                opType <= ALU_op::AND;  break;
            case 0b001: // slli
                opType <= ALU_op::SLL;  break;
            case 0b101: // srli/srai
                opType <= (take <30> (__ins) ? ALU_op::SRA : ALU_op::SRL);
        }
    }

    void work_register(int __ins) {
        if (rdBusy() || rs1Busy() || rs2Busy()) return issue_fail();
        issue_success();

        rs1Index    <= rs1(__ins);
        rs2Index    <= rs2(__ins);
        rdIndex     <= rd(__ins);
        immediate   <= immediate(); // Immediate is not used.

        iType       <= ALU_type::scalar;
        switch (funct3(__ins)) {
            default: assert(false); break;
            case 0b000: // add/sub
                opType <= (take <30> (__ins) ? ALU_op::SUB : ALU_op::ADD); break;
            case 0b001: // sll
                opType <= ALU_op::SLL; break;
            case 0b010: // slt
                opType <= ALU_op::SLT; break;
            case 0b011: // sltu
                opType <= ALU_op::SLTU; break;
            case 0b100: // xor
                opType <= ALU_op::XOR; break;
            case 0b101: // srl/sra
                opType <= (take <30> (__ins) ? ALU_op::SRA : ALU_op::SRL); break;
            case 0b110: // or
                opType <= ALU_op::OR; break;
            case 0b111: // and
                opType <= ALU_op::AND; break;
        }
    }
};


} // namespace dark

namespace dark {

void decoder::work() {
    // Decoder part.
    if (reset) {
        issue <= 0;
    } else if (!ready) {
        // Do nothing.
    } else if (empty() || nextBubble()) {
        issue <= 0;
    } else { // Non-empty and no bubble!
        int __ins = queue[head()].ins();
        int __pc  = queue[head()].pc();
        ALUPc <= __pc;

        switch (take <6,0> (__ins)) {
            case 0b0110111: // lui
                work_lui(__ins); break;
            case 0b0010111: // auipc
                work_auipc(__ins); break;
            case 0b1101111: // jal
                work_jal(__ins); break;
            case 0b1100111: // jalr
                work_jalr(__ins); break;
            case 0b1100011: // branch
                work_branch(__ins); break;
            case 0b0000011: // load
                work_load(__ins); break;
            case 0b0100011: // store
                work_store(__ins); break;
            case 0b0010011: // immediate
                work_immediate(__ins); break;
            case 0b0110011: // register
                work_register(__ins); break;
            // Vector part:
            default: assert(false, "Not implemented!"); break;
        }
    }

    // Ins queue part.
    if (reset) {
        head <= 0;
        tail <= 0;
    } else if (ready && insDone()) {
        tail <= round(tail() + 1);
        queue[tail()].ins <= insData();
        queue[tail()].pc  <= insPc();
    }
}

} // namespace dark
