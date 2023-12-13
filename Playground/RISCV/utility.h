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


struct ALU_type {
    enum {
        normal,     // Normal.
        vector,     // Vector.
        immediate,  // Immediate.
        branch,     // Branch.
        jalr,       // JALR.
        pcImm,      // PC + immediate.
        load,       // Load & store.
        store,      // Store.
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
