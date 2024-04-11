#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> index_test() {
    _Map_t map;
    using _Pair_t = typename _Map_t::value_type;

    for (size_t i = 0 ; i < _N * 2; ++i)
        map.insert(_Pair_t {i * 3, {}});

    map.clear();

    for (size_t i = 0 ; i < _N / 2; ++i)
        map.insert(_Pair_t {i * 2, {}});

    heat(map);
    size_t sum  = map.size();
    size_t time = test <1> ([&]() {
        random_machine make_acm_great_again;
        for (size_t i = 0 ; i < _N ; ++i)
            map[make_acm_great_again() % _N] = {};
    });
    for (auto [key, val] : map) sum += key + val.size();
    return {sum, time};
}

signed main() {
    random_machine test;

    using _Toy_Map_t = sjtu::map <size_t, std::string>;
    using _Std_Map_t =  std::map <size_t, std::string>;

    auto [std_sum, std_time] = index_test <_Std_Map_t> ();
    auto [toy_sum, toy_time] = index_test <_Toy_Map_t> ();

    panic_if(std_sum != toy_sum, "Your map is wrong.");

    std::cout << "Your map index [] time: " << toy_time << " ms\n";
    std::cout << "std::map index [] time: " << std_time << " ms\n";

    return global_sum < 1;
}
