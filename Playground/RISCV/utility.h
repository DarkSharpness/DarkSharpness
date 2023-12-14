#pragma once

#include "helper/hardware.h"
#include "helper/reflect.h"
#include "helper/bits.h"


namespace dark {

inline void assert(bool cond, std::string_view msg = "") {
    if (!cond) throw std::runtime_error(std::string(msg));
}

// Vector extension part.

inline constexpr int ELEN {32}; // 32 bits at one time.
inline constexpr int VLEN {64}; // 64 bits in one vector.
inline constexpr int VIDX {VLEN / ELEN} ; // 2 registers.

// Vector register.
struct vreg {
    reg data[VIDX];
    void sync() { for (auto &reg : data) reg.sync(); }
};



// ALU type code and opcode.

struct ALU_type {
    enum {
        normal,     // Normal. (rs1 and rs2 and rd)
        vector,     // Vector. (vs1 and vs2 and vd)
        immediate,  // Immediate. (rs1 and immediate and rd)
        branch,     // Branch.    (rs1 and rs2)
        jalr,       // JALR.      (rs1 and immediate and rd)
        pcImm,      // PC + immediate. (pc and immediate and rd)
        load,       // Load.    (rs1 and rs2 and immediate rd)
        store,      // Store.   (rs1 and rs2 and immediate)
    };
};

struct ALU_op {
    enum {
        ADD,
        SUB,
        SLL,
        SRL,
        SRA,
        AND,
        OR,
        XOR,
        SLT,
        SLTU,
        SGE,
        SGEU,
        SEQ,
        SNEQ
    };
};

} // namespace dark
