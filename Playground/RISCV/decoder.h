#pragma once
#include "utility.h"

namespace dark {

struct decoder {
  public:

    wire rsFull;    // Reservation station full.
    wire lsbFull;   // Load/store buffer full.
    wire robFull;   // Reorder buffer full.

    wire insDone;   // Whether the instruction is available.
    wire ins;       // Instruction to decode.
    wire insPc;     // Instruction PC.
    wire insJump;   // Whether the instruction is a jump.

  public:
    reg  issue;      // Whether to issue.

    reg  rs1Flag;    // Reorder of rs1. If highbit = 0, then rs1 available.
    reg  rs1Data;    // Source register 1.

    reg  rs2Flag;    // Reorder of rs2. If highbit = 0, then rs2 available.
    reg  rs2Data;    // Source register 2.

    reg  rdFlag;     // Whether to write back to register file.
    reg  rdIndex;    // Index in register file.

    reg  opType;     // Operation type (decoded).


};

} // namespace dark