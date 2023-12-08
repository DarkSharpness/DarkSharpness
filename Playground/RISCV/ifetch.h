#pragma once
#include "utility.h"

namespace dark {


struct ifetch {
  public:
    static constexpr int predWidth = 8; // Branch prediction width.
    static constexpr int predSize  = 1 << predWidth; // Branch prediction size.

    static constexpr int WORK = 0; // Work in one cycle.
    static constexpr int WAIT = 1; // Wait for memory.

    wire rsFull;    // Reservation station full.
    wire lsbFull;   // Load/store buffer full.
    wire robFull;   // Reorder buffer full.

    wire mcDone;    // Memory controller done.
    wire mcData;    // Memory controller data.    

    wire robEn;     // Reorder buffer enable.
    wire robPc;     // Reorder buffer PC.

    wire brType;    // Compress enable and jump result.
    wire brPc;      // PC of a branch.

  public:

    reg inst;       // Instruction.
    reg fetched;    // Whether fetched.
    reg instPc;     // Instruction PC.
    reg instJump;   // Jump or not.

    reg mcEn;   // Memory controller enable.
    reg mcPc;   // Memory controller Address.

  private:
    reg pc;     // Program counter.
    reg status; // Status of the fetcher.

    reg pred[predSize]; // Branch prediction.

    bool brEn  () { return take <1> (brJump()); }
    bool brJump() { return take <0> (brJump()); }

  public:
    void init(std::vector <wire> vec); // TODO
    void work();
    void sync();
};


} // namespace dark
