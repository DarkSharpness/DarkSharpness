#include <bits/stdc++.h>
using namespace std;

long long ran() { return rand() % (1 << 16); }

long long rand_long() {
    long long t = ran() 
                | (ran() << 16)
                | (ran() << 32)
                | (ran() << 48);
    t = abs(t) % (long long)(1e15);
    return t;
}


signed main() {
    char in[]  = "2.in";
    srand(time(NULL));
    // char out[] = "2.out";
    for(int i = 0 ; i < 8 ; ++i) {
        freopen(in,"w",stdout);
        cout << rand_long() << ' '
             << rand() % 20 << ' '
             << rand() % 20 << '\n'
             << rand_long();
        ++in[0];
        // ++out[0];
    }
    return 0;
}