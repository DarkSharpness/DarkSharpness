#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> find_test() {
    _Map_t map;
    using _Pair_t = typename _Map_t::value_type;

    for (size_t i = 0 ; i < _N ; ++i)
        map.insert(_Pair_t {i, i});

    heat(map);
    size_t sum  = map.size();
    size_t time = test <2> ([&]() {
        random_machine hastin;
        for (size_t i = 0 ; i < _N ; ++i) {
            auto iter = map.find(hastin());
            sum += (iter != map.end());
        }
    });
    return {sum, time};
}


signed main() {
    using _Toy_Map_t = sjtu::map <size_t, size_t>;
    using _Std_Map_t = std::map  <size_t, size_t>;

    auto [std_sum, std_time] = find_test <_Std_Map_t> ();
    auto [toy_sum, toy_time] = find_test <_Toy_Map_t> ();

    panic_if(std_sum != toy_sum, "Your map is wrong.");

    std::cout << "Your map find time: " << toy_time << " ms\n";
    std::cout << "std::map find time: " << std_time << " ms\n";

    return global_sum < 1;
}
