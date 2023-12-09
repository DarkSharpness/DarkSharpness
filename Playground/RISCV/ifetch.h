#pragma once
#include "utility.h"
#include "icache.h"

namespace dark {


struct ifetch {
  public:
    static constexpr int IDLE = 0; // Work in one cycle.
    static constexpr int WAIT = 1; // Wait for memory.

    wire rsFull;    // Reservation station full.
    wire lsbFull;   // Load/store buffer full.
    wire robFull;   // Reorder buffer full.

    // Case 1: hit
    // Case 2: miss and rely on fetch.

    wire hit;       // icache hit.
    wire instData;  // Instruction fetched from cache.
    wire iDone;     // Whether memory control is done.
    wire loadData;  // Instruction fetched from memory.

    wire robEn;     // Reorder buffer enable.
    wire robPc;     // Reorder buffer PC.

    // Update branch history table.
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

    bool brEn  () { return take <1> (brJump()); }
    bool brJump() { return take <0> (brJump()); }

    bool issueable() { return !(rsFull() || lsbFull() || robFull()); }

  public:
    void init(std::vector <wire> vec) {
        assert(vec.size() == 11);
        rsFull      = vec[0];
        lsbFull     = vec[1];
        robFull     = vec[2];
        hit         = vec[3];
        instData    = vec[4];
        iDone       = vec[5];
        loadData    = vec[6];
        robEn       = vec[7];
        robPc       = vec[8];
        brType      = vec[9];
        brPc        = vec[10];
    }

    void work() {
        if (reset) {
            pc      <= 0;
            status  <= IDLE;
            instRdy <= 0;
            nextPc  <= 0;
        } else if (ready) {
            if (status() == IDLE) {
                if (!issueable()) return; // Stall.
                if (hit()) { // hit and issue.
                    instRdy <= 1;
                    instOut <= instData();

                } else { // Non hit and try wait.
                    status <= WAIT;
                }
            } else {
                // Waiting for iDone signal.
                if (iDone()) {

                }

            }
        }
    }

    void sync();
};


} // namespace dark
