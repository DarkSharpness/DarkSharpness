#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 102;
struct node {
    int length;
    int data[N];
} t[N];

signed main() {
    srand(time(NULL));


    for(int i = 1 ; i <= 8 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        string str;
        const int M = (i + 2) * 10;
        int n = rand() % M;
        int q = rand() % M;

        vector <int> v = {0};
        for(int i = 1 ; i <= n ; ++i)
            v.push_back(i - n / 2);

        int maxn = 0;
        for(int j = 1 ; j <= n ; ++j) {
            t[j].length = rand() % M + rand() % M;
            if(t[j].length > 100) t[j].length = 100;
            maxn = max(maxn,t[j].length);
        }
        if(maxn < q) throw;

        for(int j = 1 ; j <= maxn ; ++j) {
            vector <int> c = v;
            random_shuffle(++c.begin(),c.end());
            for(int k = 1 ; k <= n ; ++k)
                t[k].data[j] = c[k];
        }

        freopen( in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 1 ; i <= n ; ++i) {
            dark::write(t[i].length);
            putchar(' ');
            dark::writelineRange(t[i].data + 1,t[i].length);
        }
        dark::writeline(q);

        freopen(out.data(),"w",stdout);
        int ans = 1;
        maxn = -N;
        if(q <= t[1].length) maxn = -t[1].length;
        for(int j = 2 ; j <= n ; ++j)
            if(q <= t[j].length && t[j].data[q] > maxn)
                ans = j,maxn = t[j].data[q];
        dark::writeline(ans);
    }
    return 0;
}