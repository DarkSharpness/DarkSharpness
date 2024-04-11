#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

static void inc_string(std::string &str) {
    for (auto &ch : str) {
        if (ch == '9') ch = '0';
        else { ++ch; break; }
    }
}

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> erase_test() {
    _Map_t map;
    std::string str = "00000000";
    for (size_t i = 0 ; i < _N ; ++i) {
        inc_string(str);
        map.insert({str, 42});
    }

    // Make the sequence of erase random.
    auto vec = std::vector { map.begin() };
    for (size_t i = 1 ; i < _N / 10 ; ++i) {
        vec.push_back(vec.back());
        for (int j = 0 ; j < 10 ; ++j) ++vec.back();
    }

    // Heat the map first.
    heat(map);

    size_t sum  = 0;
    size_t time = test <5> ([&]() {
        for (auto &iter : vec) map.erase(iter++), ++sum;
    });
    return {sum, time};
}


signed main() {
    using _Toy_Map_t = sjtu::map <std::string, size_t>;
    using _Std_Map_t =  std::map <std::string, size_t>;

    auto [std_sum, std_time] = erase_test <_Std_Map_t> ();
    auto [toy_sum, toy_time] = erase_test <_Toy_Map_t> ();

    panic_if(std_sum != toy_sum , "Your map is wrong.");

    std::cout << "Your map erase time: " << toy_time << " ms\n";
    std::cout << "std::map erase time: " << std_time << " ms\n";

    return global_sum < 1;
}
