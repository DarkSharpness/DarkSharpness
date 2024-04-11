#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> min_max_test() {
    _Map_t map;
    using _Pair_t = typename _Map_t::value_type;

    for (size_t i = 0 ; i < _N ; ++i)
        map.insert(_Pair_t {i, i});

    heat(map);
    size_t sum  = map.size();
    size_t time = test <5> ([&]() {
        auto temp = map.find(_N / 2);
        for (size_t i = 0 ; i < _N ; ++i) {
            if (temp == map.begin())
                map.erase(temp);
            if (temp == --map.end())
                map.erase(temp);
        }
    });
    return {sum, time};
}


signed main() {
    using _Toy_Map_t = sjtu::map <size_t, size_t>;
    using _Std_Map_t =  std::map <size_t, size_t>;

    constexpr int _Max = 2333333;

    auto [std_sum, std_time] = min_max_test <_Std_Map_t, _Max> ();
    auto [toy_sum, toy_time] = min_max_test <_Toy_Map_t, _Max> ();

    panic_if(std_sum != toy_sum, "Your map is wrong.");

    std::cout << "Your map begin/--end time: " << toy_time << " ms\n";
    std::cout << "std::map begin/--end time: " << std_time << " ms\n";

    return global_sum < 1;
}
