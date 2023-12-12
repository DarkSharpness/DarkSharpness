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

    /**
     * @return Whether the instruction is ready. (Cache hit)
     */
    const wire hit = {
        [this]()-> int { return writeEnable() || tag[index()]() == tagIn(); }
    };
    /**
     * @return The instruction fetched from icache.
     */
    const wire dataOut = {
        [this]()-> int { return writeEnable() ? dataIn() : cmd[index()](); }
    };

  private: // Private properties.

    std::array <reg, size> cmd;
    std::array <reg, size> tag;

    // These are caches to speed up fake simulation.
    // In practice, they are just wires...

    int __index  {};
    int __dataIn {};
    int __tagIn  {};

  private:

    int tagIn() { return bits {take <31, width + 2> (addrIn()) , bits <1> (1) };}
    int index() { return bits {take <width + 1 , 0> (addrIn())                };}

  public:

    // Work in one cycle.
    void work() {
        if (reset) {
            for (int i = 0 ; i < size ; ++i) {
                cmd[i] <= 0;
                tag[i] <= 0;
            }
        } else if (ready && writeEnable()) {
            // Special optimization.
            __index     = index();
            __dataIn    = dataIn();
            __tagIn     = tagIn();

            cmd[__index] <= __dataIn;
            tag[__index] <= __tagIn;
        }
    }

    void sync() {
        /* This functions is specially rewritten for better performance. */
        if (reset)
            for (int i = 0 ; i < size ; ++i) cmd[i] = 0, tag[i] = 0;
        else cmd[__index] = __dataIn, tag[__index] = __tagIn;
    }

}; // struct icache


} // namespace dark
