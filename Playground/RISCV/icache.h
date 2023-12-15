#pragma once
#include "utility.h"

namespace dark {

struct icache {
  public:
    static constexpr int width = 6;
    static constexpr int lines = 1 << width;

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
    /**
     * @return a.k.a not hit. 
     */
    const wire iFetch = {
        [this]()-> int { return !(writeEnable() || tag[index()]() == tagIn()); }
    };

  private: // Private properties.

    std::array <reg, lines> cmd;
    std::array <reg, lines> tag;

    // These are caches to speed up fake simulation.
    // In practice, they are just wires...

    int __index  {};
    int __dataIn {};
    int __tagIn  {};

  private:

    int tagIn() { return bits {take <31, width + 2> (addrIn()) , bits <1> (1) };}
    int index() { return bits {take <width + 1 , 2> (addrIn())                };}

  public:

    // Work in one cycle.
    void work() {
        if (reset) {
            for (int i = 0 ; i < lines ; ++i) {
                cmd[i] <= 0;
                tag[i] <= 0;
            }
        } else if (ready && writeEnable()) {
            // Special optimization.
            __index     = index();
            __dataIn    = dataIn();
            __tagIn     = tagIn();

            cmd.at(__index) <= __dataIn;
            tag.at(__index) <= __tagIn;
        }
    }

    void sync() {
        /* This functions is specially rewritten for better performance. */
        if (reset)
            for (int i = 0 ; i < lines ; ++i) cmd[i] = 0, tag[i] = 0;
        else cmd[__index] = __dataIn, tag[__index] = __tagIn;
    }

}; // struct icache


} // namespace dark
