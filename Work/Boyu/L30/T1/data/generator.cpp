#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1e6 + 3;
char buf[N];
int  nxt[N];

void generate(size_t n) {
    std::vector <int> v;

    for(size_t i = 0 ; i < n ; ++i) {
        if(v.size() + i == n) {
            buf[i] = ')';
            nxt[v.back()] = i;
            v.pop_back();
            continue;
        }
        buf[i] = rand() & 0b10000 ? '(' : ')';
        if(buf[i] == '(') {
            v.push_back(i);
        } else if(buf[i] == ')') {
            if(v.empty()) {
                buf[i] = '(';
                v.push_back(i);
            } else {
                nxt[v.back()] = i;
                v.pop_back();
            }
        }
    } buf[n] = 0;
    assert(v.empty());
}

signed main() {
    srand(time(NULL));
    for(int i = 2 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = i * i * i * 1000 - 2;
        freopen(in.data(),"w",stdout);
        generate(n);
        puts(buf);
        freopen(out.data(),"w",stdout);
        for(int i = 0 ; i < n ; ++i)
            if(buf[i] == '(') printf("%d ", nxt[i]);
    }
    return 0;
}
