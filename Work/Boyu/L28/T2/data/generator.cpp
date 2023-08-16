#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int get_n(int in) {
    if(in <= 3) return in * in * 10;
    if(in <= 8) return in * in * 10000;
    return 900000 + rand() % 100000;
}

int get_m(int in) {
    return pow(3,in + 2) - 1;
}

inline int get_value(char x) {
    if(!x)  return 0;
    else    return x - '0' + 1;
}

inline char get_char(int x) {
    if(!x)  return 0;
    else    return x + '0' - 1;
}

const int N = 729 * 729;
int cnt[N];

void make_buffer(char *buffer,int m) {
    buffer[0] = get_char(bool(rand() & 0b1000) + 1);
    for(int i = 1 ; i < m + 2 ; ++i) {
        int x = (rand() % 5 + 1) % 3;
        buffer[i] = get_char(x);
        if(!x) return;
    }
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = get_n(i);

        freopen(in.data(),"w",stdout);
        dark::writeline(n);

        memset(cnt,0,sizeof(cnt));
        for(int k = 0 ; k < n ; ++k) {
            char buffer[16] = {};
            make_buffer(buffer,i);
            dark::print(buffer,' ');
            int value = 0;
            for(int j = 0 ; j < 12 ; ++j)
                value = value * 3 + get_value(buffer[j]);
            ++cnt[value];
        }
        freopen(out.data(),"w",stdout);

        for(int i = 1 ; i < N ; ++i) {
            if(!cnt[i]) continue;
            char buffer[16] = {};
            int value = i;
            for(int k = 0 ; k < 12 ; ++k) {
                buffer[11 - k] = get_char(value % 3);
                value /= 3;
            }
            for(int j = 0 ; j < cnt[i] ; ++j)
                dark::print(buffer,' ');
        }
    }
    return 0;
}
