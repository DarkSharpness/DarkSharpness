#include "ans.h"

void hack_print(dynamic_bitset &a) {
    std::cout << "Size: " << a.size() << " | ";
    for (std::size_t i = 0 ; i != (a.size() + 63) / 64 * 64 ; ++i)
        std::cout << a[i];
    std::cout << '\n';
}

void print(dynamic_bitset &a) {
    std::cout << "Size: " << a.size() << " | ";
    for (std::size_t i = 0 ; i != a.size() ; ++i) std::cout << a[i];
    std::cout << '\n';
}

template <typename T>
concept check = requires(T a) {
    { a.size() }    -> std::same_as <std::size_t>;
    { a.none() }    -> std::same_as <bool>;
    { a.all()  }    -> std::same_as <bool>;

    { a.set() }     -> std::same_as <dynamic_bitset &>;
    { a.flip()  }   -> std::same_as <dynamic_bitset &>;
    { a.reset() }   -> std::same_as <dynamic_bitset &>;

    { a |= a }      -> std::same_as <dynamic_bitset &>;
    { a &= a }      -> std::same_as <dynamic_bitset &>;
    { a ^= a }      -> std::same_as <dynamic_bitset &>;

    { a <<= 1 }     -> std::same_as <dynamic_bitset &>;
    { a >>= 1 }     -> std::same_as <dynamic_bitset &>;

    { a[0] }            -> std::same_as <bool>;
    { a.set(0) }        -> std::same_as <dynamic_bitset &>;
    { a.set(0, 0) }     -> std::same_as <dynamic_bitset &>;
    { a.push_back(0) }  -> std::same_as <dynamic_bitset &>;
} && std::constructible_from <dynamic_bitset, T>
  && std::constructible_from <dynamic_bitset, std::size_t>
  && std::is_copy_constructible_v <T>
  && std::is_default_constructible_v <T>
  && std::is_copy_assignable_v <T>;

template <check T = dynamic_bitset>
void func() {
    T a(100);

    a.flip();
    a <<= 27;

    print(a);
}

signed main() {
    func();
    return 0;
}

