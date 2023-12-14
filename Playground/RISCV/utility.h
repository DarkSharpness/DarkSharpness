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
struct vreg : public std::array <reg, VIDX> {
    void sync() { for (auto &reg : *this) reg.sync(); }
};

struct vwire : public std::array <wire, VIDX> {
    void sync() { /* Still do nothing. */}
};


// ALU type code and opcode.

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

/**
 * Bit 0: use rs1 (true) / pc (false)
 * Bit 1: use rs2 (true) / imm (false)
 * Bit 2: is jalr   (pc + 4 -> rd, rs1 + imm -> pc)
 * Bit 3: is branch (rs1 <comp> rs2)
 * Bit 4: is load   (M[rs1 + imm] -> rd)
 * Bit 5: is store  (rs2 -> M[rs1 + imm])
 * Bit 6: is vector (change 'r' to 'v')
 * 
 * If load/store, then higher 3 bits are funct3 of load/store.
 * In fact, it should be a combination of several bits.
 * It is just meant to speed up C++ simulation.
 * In verilog, it should be 8 wires.
 */
struct ALU_type {
    enum {
        scalar  = 0b0000011,        // rs1 <op> rs2 -> rd
        jalr    = 0b0000111,        // pc + 4 -> rd, rs1 + imm -> pc
        branch  = 0b0001011,        // rs1 <comp> rs2
        load    = 0b0010011,        // M[rs1 + imm] -> rd
        store   = 0b0100011,        // rs2 -> M[rs1 + imm]
        vector  = 0b1000011,        // vs1 <op> vs2 -> vd

        pcImm       = 0b0000000,    // pc  <op> imm -> rd
        immediate   = 0b0000001,    // rs1 <op> imm -> rd
    };
    inline static constexpr int width = 7;

    static bool isVector(int type) { return take <6> (type);    }
    static bool isScalar(int type) { return !isVector(type);    }
    static bool isMemory(int type) { return take <5,4> (type);  }
    static bool isBranch(int type) { return take <3> (type);    }
    static bool isJalr(int type)   { return take <2> (type);    }
    static bool useRs1(int type)   { return take <0> (type);    }
    static bool useRs2(int type)   { return take <1> (type);    }
    static bool useRd (int type)   { return !take <6,3> (type); }
    static bool isLoad (int type)  { return take <5> (type);    }
    static bool isStore(int type)  { return take <4> (type);    }

    static auto funct3  (int type) { return take <width + 2, width> (type); }
    static bool funct3_1(int type) { return take <width + 2>        (type); }
    static int  funct3_2(int type) { return take <width + 1, width> (type); }
};


} // namespace dark
