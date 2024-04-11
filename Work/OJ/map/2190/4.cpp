#include "src.hpp"
#include "helper.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename _Map_t, size_t _N = 1919810>
__attribute__((noinline))
inline std::pair <size_t, size_t> insert_test() {
    _Map_t map;
    using _Pair_t = typename _Map_t::value_type;

    for (size_t i = 0 ; i < _N ; ++i)
        map.insert(_Pair_t {i, {}});

    /**
     * This may look weird, why we clear the map here?
     * That's because we want to preheat the suitable
     * node pool for the map.
     */
    size_t sum  = map.size();
    map.clear();
    size_t time = test <1> ([&]() {
        random_machine wankupi_is_so_cute;
        for (size_t i = 0 ; i < _N ; ++i)
            map.insert(_Pair_t {wankupi_is_so_cute(), {}});
    });
    return {sum, time};
}

signed main() {
    using _Toy_Map_t = sjtu::map <size_t, std::string>;
    using _Std_Map_t =  std::map <size_t, std::string>;

    auto [std_sum, std_time] = insert_test <_Std_Map_t> ();
    auto [toy_sum, toy_time] = insert_test <_Toy_Map_t> ();

    panic_if(std_sum != toy_sum, "Your map is wrong.");

    std::cout << "Your map insert time: " << toy_time << " ms\n";
    std::cout << "std::map insert time: " << std_time << " ms\n";

    return global_sum < 1;
}
