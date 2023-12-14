#pragma once
#include "utility.h"

namespace dark {

struct scalar_input {
    wire issue;     // Whether to issue.
    wire iType;     // Instruction type for ALU.

    wire ALUPc;     // Pc for ALU.
    wire immediate; // Immediate value.

    wire rs1Data;   // Data of rs1.
    wire rs2Data;   // Data of rs2.

    wire opType;        // Operation type for ALU.
    wire isBubbling;    // Whether is bubbling.
};

struct scalar_output {
    reg scalarOut;  // Only output of scalar ALU.
};

struct scalar_ALU : scalar_input, scalar_output {
  public:
    void work() {
        if (reset) {
            // Do nothing.
        } else if (!ready) {
            // Do nothing.
        } else if (issue() && ALU_type::isScalar(iType())) {
            scalarOut <= result(rs1Real(), rs2Real(), opType());
        }
    }

    void sync() { scalarOut.sync(); }

  private:
    int rs1Real() const { return ALU_type::useRs1(iType()) ? rs1Data() : ALUPc();       }
    int rs2Real() const { return ALU_type::useRs2(iType()) ? rs2Data() : immediate();   }

    /* A wire of all ALU units! */
    static int result(int x, int y,int op) {
        switch (op) {
            case ALU_op::ADD:   return x + y;
            case ALU_op::SUB:   return x - y;
            case ALU_op::SLL:   return x << y;
            case ALU_op::SRL:   return unsigned(x) >> y;
            case ALU_op::SRA:   return signed(x) >> y;
            case ALU_op::AND:   return x & y;
            case ALU_op::OR:    return x | y;
            case ALU_op::XOR:   return x ^ y;
            case ALU_op::SLT:   return x < y;
            case ALU_op::SLTU:  return (unsigned)x < (unsigned)y;
            case ALU_op::SGE:   return x >= y;
            case ALU_op::SGEU:  return (unsigned)x >= (unsigned)y;
            case ALU_op::SEQ:   return x == y;
            case ALU_op::SNEQ:  return x != y;
            default: assert(false, "Unknown ALU operation.");
        }
    }
};


} // namespace dark
