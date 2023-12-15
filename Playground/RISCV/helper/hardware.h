#pragma once
#include "debug.h" // If you want to use debug, include this.
#include <functional>
#include <stdexcept>


/* Declaration of basic register and wire type. */
namespace dark {

struct wire;


namespace detail {

template <typename _Func>
concept wire_lambda =
    !std::same_as <wire, std::decay_t <_Func>> &&
    requires(_Func &&__f) { { __f() } -> std::same_as <int>; };

struct wire_base {
    using _Ret = int;
    using _Cpy = wire_base *;
    virtual _Ret call()     = 0;
    virtual _Cpy copy()     = 0;
    virtual ~wire_base() = default;
};

template <typename _Func>
struct wire_implement final : wire_base {
    static_assert (std::same_as <std::decay_t <_Func>, _Func>);
    _Func lambda;
    wire_implement(const _Func &__func) : lambda(__func) {}
    wire_implement(_Func &&__func) : lambda(std::move(__func)) {}
    ~wire_implement() = default;

    _Ret call()     override { return lambda(); }
    _Cpy copy()     override { return new wire_implement(lambda); }
};

}


/**
 * @brief Simulator wire.
 * For better constructor (use {} initialization),
 * we have to make public its member variable.
 */
struct wire {
//   private:
    using _Manage = detail::wire_base;
    _Manage *manage {};

  public:
    wire() = default;
    ~wire() { delete manage; }

    wire(const wire &other) : manage(other.manage->copy()) {}
    wire(wire &&other) noexcept : manage(other.manage) { other.manage = nullptr; }

    template <detail::wire_lambda _Func>
    wire(_Func &&__func) {
        using _Real = std::decay_t <_Func>;
        manage = new detail::wire_implement <_Real>
            (std::forward <_Func> (__func));
    }

    wire &operator = (const wire &rhs) {
        if (this != &rhs) { this->~wire(); ::new (this) wire(rhs); } return *this;
    }
    wire &operator = (wire &&rhs) noexcept {
        if (this != &rhs) { this->~wire(); ::new (this) wire(std::move(rhs)); } return *this;
    }

    int operator() (void) const {
        if (!manage) throw std::runtime_error("Uninitialized wire.");
        return manage->call();
    }
};

/**
 * @brief Simulator register.
 * On consideration of type safety,
 * we make private its member variables.
 */
struct reg {
//   private:
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
    void sync() { debug("Sync reg:", this, this->value, this->bak); value = bak; }

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
