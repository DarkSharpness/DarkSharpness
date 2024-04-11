#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> visit_test() {
    _Map_t map;
    using _Pair_t = typename _Map_t::value_type;

    for (size_t i = 0 ; i < _N ; ++i)
        map.insert(_Pair_t {i, i});

    heat(map);

    size_t sum  = map.size();
    size_t time = test <20> ([&]() {
        for (auto iter : map)
            sum += iter.second + iter.first;
    });
    return {sum, time};
}


signed main() {
    using _Toy_Map_t = sjtu::map <int, int>;
    using _Std_Map_t =  std::map <int, int>;

    auto [std_sum, std_time] = visit_test <_Std_Map_t> ();
    auto [toy_sum, toy_time] = visit_test <_Toy_Map_t> ();

    auto [toy_sum_2, toy_time_2] = visit_test <_Toy_Map_t> ();
    auto [std_sum_2, std_time_2] = visit_test <_Std_Map_t> ();

    std_sum += std_sum_2;
    toy_sum += toy_sum_2;
    std_time += std_time_2;
    toy_time += toy_time_2;

    panic_if(std_sum != toy_sum, "Your map is wrong.");

    std::cout << "Your map visit time: " << toy_time << " ms\n";
    std::cout << "std::map visit time: " << std_time << " ms\n";

    return global_sum < 1;
}
