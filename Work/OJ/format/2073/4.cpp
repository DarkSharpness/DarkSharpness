#include "src.hpp"
#include "utility.h"

#include <iostream>

void test_0(std::size_t n) {
    try {
        sjtu::format("Hello, world! {} \n");
    } catch(const std::exception& e) {
        std::cout << sjtu::format(
            "You pass testpoint {}! {}\n",
            n , "Congratulations!"
        );
    }
}

void test_1(std::size_t n) {
    try {
        sjtu::format("Hello, world! {} {1} {}\n", 1, 2, 3);
    } catch(const std::exception& e) {
        std::cout << sjtu::format(
            "You pass testpoint {}! {}\n",
            n , "Congratulations!"
        );
    }
}

void test_2(std::size_t n) {
    try {
        sjtu::format("Hello, world! { }\n", 1, 2, 3);
    } catch(const std::exception& e) {
        std::cout << sjtu::format(
            "You pass testpoint {}! {}\n",
            n, "Congratulations!"
        );
    }
}

void test_3(std::size_t n) {
    try {
        sjtu::format("Hello, world! {10} {1} {0}\n", 1, 2, 3);
    } catch(const std::exception& e) {
        std::cout << sjtu::format(
            "You pass testpoint {}! {}\n",
            n , "Congratulations!"
        );
    }
}

void test_4(std::size_t n) {
    try {
        sjtu::format("Hello, world! {{{{{{}}}}}\n", 1, 2, 3);
    } catch(const std::exception& e) {
        std::cout << sjtu::format(
            "You pass testpoint {}! {}\n",
            n , "Congratulations!"
        );
    }
}

template <typename T, std::size_t N>
constexpr std::size_t array_length(T (&)[N]) { return N; }


signed main() {
    using _Func_type = decltype(test_0) *;
    _Func_type test[] = {test_0, test_1, test_2, test_3, test_4};
    for (std::size_t i = 0; i < array_length(test) ; ++i) test[i](i);
    return 0;
}
