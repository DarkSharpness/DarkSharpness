#pragma once
#include "utility.h"

namespace dark {

struct icache {
  public:
    static constexpr int width = 8;
    static constexpr int size  = 1 << width;

    wire addrIn;
    wire writeEnable;
    wire dataIn;

  public:
    wire hit() {
        return { [this] -> int { return tag[index()]() == tagIn(); } };
    }
    wire dataOut() {
        return { [this] -> int { return cmd[index()](); } };
    }

  private:
    reg  cmd[size];
    reg  tag[size];

    int tagIn() { return take <31, width + 2> (addrIn()) << 1 | 1; }
    int index() { return take <width + 1 , 0> (addrIn());          }

  public:

    // Link the lines.
    void init(std::vector <wire> vec) {
        addrIn          = vec[0];
        writeEnable     = vec[1];
        dataIn          = vec[2];
    }

    // Work in one cycle.
    void work() {
        if (reset) {
            for (int i = 0 ; i < size ; ++i) {
                cmd[i] <= 0;
                tag[i] <= 0;
            }
        } else if (ready && writeEnable()) {
            cmd[index()] <= dataIn();
            tag[index()] <= tagIn();
        }
    }

    // Synchronize all registers
    void sync() {
        for (int i = 0 ; i < size ; ++i) { cmd[i].sync(); tag[i].sync(); }
    }
}; // struct icache


} // namespace dark
