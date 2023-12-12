#pragma once
#include "utility.h"

namespace dark {

struct reservation_station {
  public:
    wire issue;      // Whether to issue.

    wire rs1Flag;    // Reorder of rs1. If highbit = 0, then rs1 available.
    wire rs1Data;    // Source register 1.

    wire rs2Flag;    // Reorder of rs2. If highbit = 0, then rs2 available.
    wire rs2Data;    // Source register 2.

    wire rdFlag;     // Whether to write back to register file.
    wire rdIndex;    // Index in register file.

    wire opType;     // Operation type (decoded).

    wire lsbUpdate;  // Load update from load/store buffer.
    wire lsbIndex;   // Load/store buffer update index.
    wire lsbData;    // Load/store buffer update data.

  public:
    wire full;      // Reservation station full.

    reg update;    // Update value calculated.
    reg updateRob; // Update reorder buffer index.
    reg updateVal; // Update value.

  public: // This part should be private.


  public:



};


} // namespace dark