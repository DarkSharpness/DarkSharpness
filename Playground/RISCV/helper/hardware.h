#pragma once
#include <functional>
#include <stdexcept>
#include <iostream> // Debug only.

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
    void sync() { std::cerr << "wire\n"; /* Do nothing!!! */ }
};

/**
 * @brief Simulator register.
 * On consideration of type safety,
 * we make private its member variables.
 */
struct reg {
  private:
    int value {};
    union { int  bak {}; char dat[4]; };
  public:

    int operator() (void) const { return value; }
    operator wire() { return { [this] () -> int { return value; } }; }

    void operator = (int val) { value = bak = val; }
    void operator = (reg rhs) { value = bak = rhs.value; }
    void operator <= (int val) { bak = val; }
    void operator <= (reg rhs) { bak = rhs.value; } 
    void sync() { value = bak; std::cerr << "reg\n"; }

    // Set given byte to given char (indexed from 0, low byte).
    template <int l> requires (l >= 0 && l < 4)
    void set_byte(char val) { dat[l] = val; }
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
