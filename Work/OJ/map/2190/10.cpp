#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> copy_test() {
    _Map_t map;
    using _Pair_t = typename _Map_t::value_type;

    for (size_t i = 0 ; i < _N * 2; ++i)
        map.insert(_Pair_t {i, {}});

    map.clear();

    for (size_t i = 0 ; i < _N; ++i)
        map.insert(_Pair_t {i, {}});

    heat(map);
    size_t sum  = map.size();
    size_t time = test <1> ([&]() {
        _Map_t copy = map;
    });
    return {sum, time};
}

signed main() {
    random_machine test;

    using _Toy_Map_t = sjtu::map <size_t, size_t>;
    using _Std_Map_t =  std::map <size_t, size_t>;

    auto [std_sum, std_time] = copy_test <_Std_Map_t> ();
    auto [toy_sum, toy_time] = copy_test <_Toy_Map_t> ();

    auto [toy_sum_2, toy_time_2] = copy_test <_Toy_Map_t> ();
    auto [std_sum_2, std_time_2] = copy_test <_Std_Map_t> ();

    std_sum += std_sum_2;
    toy_sum += toy_sum_2;
    std_time += std_time_2;
    toy_time += toy_time_2;

    panic_if(std_sum != toy_sum, "Your map is wrong.");

    std::cout << "Your map copy & clear time: " << toy_time << " ms\n";
    std::cout << "std::map copy & clear time: " << std_time << " ms\n";

    return global_sum < 1;
}
