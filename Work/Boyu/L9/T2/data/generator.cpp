#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

inline int rand_in(int a,int b) {
    return abs(rand() << 16 | rand()) % (b - a + 1) + a;
}

int a[] = {1,2,3,4,5,
           10,100,1000,1000,10000};
int b[] = {10,10,10,10,100,
           100,1000,5000,10000,100000};



signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        vector <int> cnt = vector (101,0);
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        int n = rand_in(a[i - 1],b[i - 1]); 
        freopen(in.c_str(),"w",stdout);
        dark::writeline(n);
        for(int i = 0 ; i < n ; ++i) {
            int x = rand_in(1,100);
            dark::write(x);putchar(' ');
            ++cnt[x];
        }
        freopen(out.c_str(),"w",stdout);
        int loc = 0;
        cnt[0] = 0;
        for(int i = 1 ; i <= 100 ; ++i)
            if(cnt[i] >= cnt[loc]) loc = i;
        dark::write(loc);
    }
    return 0;
}
