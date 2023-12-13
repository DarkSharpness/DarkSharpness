#pragma once
#include "utility.h"

namespace dark {


struct register_input {
    // Query before issue.

    wire rs1;       // Index of the register to read.
    wire rs2;       // Index of the register to read.
    wire rd;        // Index of the register to write.

    // Set busy after issue.

    wire issue;     // Whether to issue.
    wire issueRd;   // Whether to issue and write back to rd.   

    wire wbDone;    // Whether write back is done.
    wire wbData;    // Data to write back.
};


struct register_private {
    std::array <reg, 32> regs;
    reg busy; /* Whether busy. (Busy[0] is always false) */
};

/**
 * @brief Register file for scalar registers.
 */
struct register_file : public register_input , private register_private {
    using sync = sync_tag <register_private>;
    friend class caster <register_file>;

    const wire rs1Data() { return regs[rs1()]; }
    const wire rs2Data() { return regs[rs2()]; }

    const wire rs1Busy() { return { [this] -> int { return test_busy(rs1()); }}; }
    const wire rs2Busy() { return { [this] -> int { return test_busy(rs2()); }}; }
    const wire rdBusy()  { return { [this] -> int { return test_busy(rd ()); }}; }

    void work() {
        if (reset) {
            for (auto &reg : regs) reg <= 0;
            busy <= 0; // Not busy.
        } else if (!ready) {
            // Do nothing.
        } else { // Normal work.
            if (issue() && issueRd()) {
                busy.set_bit(issueRd(), true);
            } else if (wbDone() && wbData()) {
                busy.set_bit(wbDone(), false);
                regs[wbDone()] <= wbData();
            }
        }
    }

  private:
    // Test whether the register is really busy.
    bool test_busy(int x) { return x && (busy[x] || (issue() && issueRd() == x)); }
};

} // namespace dark


namespace dark {

/**
 * @brief Register file for vector registers.
 */
struct vector_file {
    std::array <reg, VIDX * 32> regs;
};


} // namespace dark