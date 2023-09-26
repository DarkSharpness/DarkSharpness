#include <bits/stdc++.h>
// #include <Dark/inout>


struct MineFucker {
    inline static constexpr size_t N = 102;
    enum node : uint8_t {
        /* 0 ~ 8: Safe with number of mine.  */
        IS_SAFE = 0b00001000, /* Threshold of safe. */
        IS_MINE = 0b10000000, /* A mine. */
        UNKNOWN = 0b01000000, /* Unknown. */
        IF_MINE = 0b10100000, /* Possible mine. */
        IF_SAFE = 0b01100000, /* Possible safe. */
        BORDER  = 0b00010000, /* Border case. */
    };
    static_assert(sizeof(node) == 1);

    bool is_safe(node __val) noexcept {
        return __val <= IS_SAFE;
    } 

    bool is_unknown(node __val) noexcept {
        return __val == UNKNOWN;
    }

    bool is_mine(node __val) noexcept {
        return __val == IS_MINE;
    }

    bool may_be_mine(node __val) {
        return __val & IS_MINE;
    }

    node data[N][N];
    const int col = 3;
    const int row = 3;

    template <class _Func>
    int collect(int x,int y,_Func &&__func) {
        int ans = 0;
        for(int i = -1 ; i <= 1 ; ++i)
            for(int j = -1 ; j <= 1 ; ++j)
                ans += __func(data[x + i][y + j]);
        return ans;
    }

    void update_mine(int x,int y) {
        for(int i = -1 ; i <= 1 ; ++i)
            for(int j = -1 ; j <= 1 ; ++j)
                if (is_unknown(data[x + i][y + j]))
                    data[x + i][y + j] = IS_MINE;
    }

    void check() {
        for(int i = 1 ; i <= col ; ++i) {
            for(int j = 1 ; j <= row ; ++j) {
                if (!is_safe(data[i][j])) continue;
                if (collect(i,j,is_unknown) == data[i][j])
                    update_mine(i,j);


            }
        }
    }


};


signed main() {


    return 0;
}
