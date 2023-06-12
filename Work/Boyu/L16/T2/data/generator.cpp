#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int a[200];
int t[200];

signed main() {
    srand(time(NULL));
    for(int tt = 1 ; tt <= 10 ; ++tt) {
        string in  = to_string(tt) + ".in";
        string out = to_string(tt) + ".out";
        freopen(in.c_str(),"w",stdout);
        int n = rand() % (10 * tt) + 1;
        for(int i = 1 ; i <= n ; ++i)
            a[i] = rand() % (6 * tt) + 1;
        int q = rand() % (10 * tt) + 1;


        dark::writeline(n,q);
        dark::writelineRange(a + 1,n);

        for(int i = 0 ; i < q ; ++i)
            dark::writeline(t[i] = rand() % (7 * tt) + 1);

        freopen(out.c_str(),"w",stdout);
        for(int j = 0 ; j < q ; ++j) {
            int count = 0;
            for(int i = 1 ; i <= n ; ++i)
                if(a[i] == t[j]) {
                    ++count;
                    dark::print(i,' ');
                }
            if(count == 0) putchar('0');
            putchar('\n');
        }
    }
    return 0;
}