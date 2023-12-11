#include "src.hpp"
#include <iostream>
#include <vector>

signed main() {
    using koishi::any;
    static_assert (sizeof(any) == sizeof(void *), "any size is wrong");
    static_assert (alignof(any) == alignof(void *), "any alignment is wrong");
    std::cout << std::boolalpha;

    any a = nullptr;
    std::cout << a.is_empty() << '\n';

    any b = std::move(a);
    std::cout << b.is_empty() << '\n';

    try {
        b.cast <std::nullptr_t> ();
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
