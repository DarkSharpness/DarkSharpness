#include <iostream>
#include <cstdint>
#include <array>
#include <cstring>
#include <queue>
#include <bitset>

constexpr int M = 9; /* 9-bits */
/**
 * 0 1 2
 * 3 4 5
 * 6 7 8 
*/
using _State = std::uint64_t;
using _Map   = std::array <std::uint64_t, 1 << M>;

template <size_t ...__pos>
constexpr _State make_state() { return ((_State(1) << __pos) | ...); }

constexpr _State influence[M] = {
    make_state <0, 1, 3> (),
    make_state <0, 1, 2, 4> (),
    make_state <1, 2, 5> (),
    make_state <0, 3, 4, 6> (),
    make_state <1, 3, 4, 5, 7> (),
    make_state <2, 4, 5, 8> (),
    make_state <3, 6, 7> (),
    make_state <4, 6, 7, 8> (),
    make_state <5, 7, 8> ()
};

constexpr std::uint64_t kINIT = std::uint64_t(-1);

constexpr _Map init_map() {
    _Map ret = {};
    for(auto &__idx : ret) __idx = kINIT;
    return ret;
}

_Map step = init_map();

char read_char() {
    char c = std::getchar();
    while(c != '0' && c != '1') c = std::getchar();
    return c;
}

signed main() {
    _State init = {};
    for(int i = 0 ; i < 9 ; ++i)
        init |= (read_char() == '1') << i;

    std::queue <_State> q;
    q.push(init);

    step[init] = 0;
    while(!q.empty()) {
        auto __tmp = q.front(); q.pop();
        for(auto __inf : influence) {
            auto __new = __tmp ^ __inf;
            if (step[__new] != kINIT) continue;
            step[__new] = step[__tmp] + 1;
            q.push(__new);
        }
    }
    std::cout << step[(_State{1} << M) - 1] << std::endl;
    return 0;
}
