#pragma once
#include "utility.h"

namespace dark {

struct predictor {
  public:
    static constexpr int width = 8;             // Branch prediction width.
    static constexpr int size  = 1 << width;    // Branch prediction size.

    wire cmd;    // Command from ifetch.
    wire pc;     // Program counter.

    wire brType; // 00: Nothing, 10: result stay, 11: result jump.
    wire brPc;   // Branch target.

  public:

    wire jump()     {
        return {
            [this] () -> int {
                if (take <6,0 > (cmd())) 
                


            }
        };
    }
    wire nxtPc()    {}

  private:
    reg table[size]; // Branch prediction.

  public:
    void init(std::vector <wire> vec) {
        cmd     = vec[0];
        pc      = vec[1];
        brType  = vec[2];
        brPc    = vec[3];
    }

    void work() {
        if (reset) {
            for (int i = 0; i < size; ++i) table[i] <= 0;
        } else if (ready) {
            auto __brType   = brType(); // Speed up by caching.
            auto __index    = take <width + 1, 2> (pc());
            auto &__dat     = table[__index];
            if (take <1> (__brType)) {
                if (take <0> (__brType)) { // Jump
                    switch (__dat()) {
                        default: assert(false);
                        case 0:     __dat <= 1; break;
                        case 1:     __dat <= 1; break;
                        case -1:    __dat <= 0; break;
                        case -2:    __dat <= -1; break;
                    }
                } else {
                    switch (__dat()) {
                        default: assert(false);
                        case 0:     __dat <= -1; break;
                        case 1:     __dat <= 0;  break;
                        case -1:    __dat <= -2; break;
                        case -2:    __dat <= -2; break;
                    }
                }
            }
        }
    }
};


} // namespace dark
