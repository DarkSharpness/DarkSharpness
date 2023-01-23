// Testing the implement of standard C++ library.
// #pragma GCC optimize(3)
#include <iostream>
#include <vector>

struct object {
    void * ptr;
    size_t val;
    object() {std::cout << "Construction.\n";}
    object(object &&) noexcept {std::cout << "Move Construction.\n";}
    object(const object &) {std::cout << "Copy Construction.\n";}
    object &operator = (object &&) {
        std::cout << "Move Assignment.\n";
        return *this;
    }
    object &operator = (const object &) {
        std::cout << "Copy Assignment.\n";
        return *this;
    }
};

inline void printline() {std::cout << "----------------------\n";}

signed main() {
    std::vector <object> test = {object()};
    printline();
    test.resize(3); // test.emplace_back();
    object A;
    printline();
    test.emplace_back();
    test.size();
    test.clear();
    *test.crbegin();
    // std::vector <int> vec = std::vector <int>(3);
    return 0;
}
