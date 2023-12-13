#pragma once
#include "debug.h" // If you want to use debug, include this.
#include <functional>
#include <stdexcept>


/* Declaration of basic register and wire type. */
namespace dark {

/**
 * @brief Simulator wire.
 * For better constructor (use {} initialization),
 * we have to make public its member variable.
 */
struct wire {
    std::function <int (void)> func;
    int operator() (void) const { return func(); }
    void sync() { debug("Sync wire:", this); }
};

/**
 * @brief Simulator register.
 * On consideration of type safety,
 * we make private its member variables.
 */
struct reg {
  private:
    int value {};
    int bak   {};
  public:

    int operator() (void) const { return value; }
    bool operator[] (int x) const { return (value >> x) & 1; }

    operator wire() { return { [this] () -> int { return value; } }; }

    void operator = (int val) { value = bak = val; }
    void operator = (reg rhs) { value = bak = rhs.value; }
    void operator <= (int val) { bak = val; }
    void operator <= (reg rhs) { bak = rhs.value; } 
    void sync() { debug("Sync reg:", this, this->value, this->bak); value = bak;  }

    // Set given byte to given char (indexed from 0, low byte).
    template <int l> requires (l >= 0 && l < 4)
    void set_byte(char val) {
        bak &= ~(0xff << (l * 8));
        bak |= unsigned(val) << (l * 8);
    }

    void set_bit(int l, bool val) {
        bak &= ~(1 << l);
        bak |= val << l;
    }
};


inline bool clock {}; // Clock signal. Its actually useless...
inline bool reset {}; // Reset signal. Reset all registers if high.
inline bool ready {}; // Ready signal. Stall the CPU temporarily if low.
inline bool stall {}; // Stall signal. Stop the program and exit if high.

// Not implemented wire. Throw if called.
inline const wire NotImplemented = {
    [] () -> int { throw std::runtime_error("Not implemented"); }
};

} // namespace dark
