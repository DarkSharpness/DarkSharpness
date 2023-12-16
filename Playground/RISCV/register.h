#pragma once
#include "utility.h"

namespace dark {


struct scalar_input {
    // Query busy before issue.
    wire rs1;       // Index of the register to read.
    wire rs2;       // Index of the register to read.
    wire rd;        // Index of the register to write.

    // Query data after issue.
    wire rs1ALU;    // Data of rs1.
    wire rs2ALU;    // Data of rs2.

    // Set busy after issue.
    wire issue;     // Whether to issue.
    wire issueRd;   // Whether to issue and write back to rd.   

    wire wbDone;    // Whether write back is done.
    wire wbData;    // Data to write back.
};


struct scalar_private {
    std::array <reg, 32> regs;
    reg busy; /* Whether busy. (Busy[0] is always false) */
};

/**
 * @brief Register file for scalar registers.
 */
struct scalar_file : public scalar_input , private scalar_private {
    using sync = sync_tag <scalar_private>;
    friend class caster <scalar_file>;

    const wire rs1Data = { [this]() -> int { return regs[rs1ALU()](); } };
    const wire rs2Data = { [this]() -> int { return regs[rs2ALU()](); } };

    const wire rs1Busy = { [this]() -> int { return test_busy(rs1()); }};
    const wire rs2Busy = { [this]() -> int { return test_busy(rs2()); }};
    const wire rdBusy  = { [this]() -> int { return test_busy(rd ()); }};

    void work() {
        if (reset) {
            for (auto &reg : regs) reg <= 0;
            busy <= 0; // Not busy.
        } else if (!ready) {
            // Do nothing.
        } else { // Normal work.
            assert(!(issue() && wbDone() && issueRd() == wbDone()));
            assert(issueRd() < 32 && wbDone() < 32 , "??");

            if (issue() && issueRd()) {
                busy.set_bit(issueRd(), true);
            }

            if (wbDone()) {
                busy.set_bit(wbDone(), false);
                regs[wbDone()] <= wbData();
            }
        }

        assert(regs[0]() == 0, "Register 0 is always 0.");
        details("Scalar file:"
            "   ra =", regs[1].next(),
            "|  sp =", regs[2].next(), 
            "| a0 =", regs[10].next(),
            "| a1 =", regs[11].next(),
            "| a2 =", regs[12].next(),
            "| a3 =", regs[13].next(),
            "| a4 =", regs[14].next(),
            "| a5 =", regs[15].next(),
            "| busy =", busy.next()
            );

    }

    int return_value() const { return regs[10](); }

  private:
    // Test whether the register is really busy.
    bool test_busy(int x) const {
        return
            (busy[x]   && x != wbDone())    // Old busy.
        || (new_busy() && x == issueRd());  // New busy.
    }
    // A new_made busy register.
    bool new_busy() const { return issue() && issueRd(); }
};


} // namespace dark


namespace dark {

/**
 * @brief Register file for vector registers.
 */
struct vector_file {
    std::array <vreg,  32> regs;
};


} // namespace dark