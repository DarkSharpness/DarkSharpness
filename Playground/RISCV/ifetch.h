#pragma once
#include "utility.h"
#include "icache.h"

namespace dark {


struct ifetch {
  public:
    static constexpr int width = 8;             // Branch prediction width.
    static constexpr int size  = 1 << width;    // Branch prediction size.

    static constexpr int IDLE = 0; // Work in one cycle.
    static constexpr int WAIT = 1; // Wait for memory.

    wire rsFull;    // Reservation station full.
    wire lsbFull;   // Load/store buffer full.
    wire robFull;   // Reorder buffer full.

    // Case 1: hit
    // Case 2: miss and rely on fetch.

    wire instEn;    // icache hit.
    wire instData;  // Instruction fetched from cache.
    wire iDone;     // Whether memory control is done.
    wire loadData;  // Instruction fetched from memory.

    wire robEn;     // Reorder buffer enable.
    wire robPc;     // Reorder buffer PC.

    wire brType;    // Compress enable and jump result.
    wire brPc;      // PC of a branch.

  public:

    reg instRdy;    // Whether fetched.
    reg instOut;    // Instruction fetched.
    reg nextPc;     // Instruction PC (next command).
    reg instJump;   // Jump or not (branching).

    reg opType;
    reg rs1Index;
    reg rs2Index;
    reg rdIndex;
    reg immData;

  private:
    reg pc;     // Program counter.
    reg status; // Status of the fetcher.

    reg pred[size]; // Branch prediction.

    bool brEn  () { return take <1> (brJump()); }
    bool brJump() { return take <0> (brJump()); }

  public:
    void init(std::vector <wire> vec);
    void work();
    void sync();
};


} // namespace dark
