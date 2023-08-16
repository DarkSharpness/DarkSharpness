#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


struct node {
    int t :  1;
    int x : 31;
    int y : 32;
} t[10003];
const int N = 1e5 + 3;
std::array <int,36> len,tag;
int a[36][N];



signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 9 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = i * 3;
        const int m = i * 10;
        freopen(in.c_str(),"w",stdout);
        dark::writeline(n,m);

        for(int i = 1 ; i <= n ; ++i) {
            len[i] = rand() % m + 10;
            dark::write(len[i]); putchar(' ');
            for(int j = 0 ; j < len[i] ; ++j)
                a[i][j] = (rand() | rand() << 16) % (i * i * (i - 1) + 1000) + 1;
            std::sort(a[i],a[i] + len[i]);
            dark::writelineRange(a[i],a[i] + len[i]);
        }

        {
            std::size_t sum = 0;
            std::array <int,36> tmp = len;
            for(int i = 0 ; i < m ; ++i) {
                t[i] = (node) {bool(rand() & 0b100),rand() % n + 1,rand() % n + 1};
                if(t[i].t) {
                    if(tmp[t[i].x] + tmp[t[i].y] > 1e5 - 2) --i;
                    else tmp[t[i].x] += tmp[t[i].y];
                } else {
                    if(sum + tmp[t[i].x] > 1e6 - 2) --i;
                    else sum += tmp[t[i].x];
                }
            }
        }
        for(int i = 0 ; i < m ; ++i) {
            if(t[i].t) {
                dark::writeline("add",t[i].x,t[i].y);
            } else {
                dark::writeline("print",t[i].x);
            }
        }
        freopen(out.c_str(),"w",stdout);
        for(int i = 0 ; i < m ; ++i) {
            if(t[i].t) {
                int x = t[i].x;
                int y = t[i].y;
                memcpy(a[x] + len[x],a[y],sizeof(int) * len[y]);
                len[x] += len[y];
                tag[x] = 1;
            } else {
                int x = t[i].x;
                if(tag[x]) {
                    std::sort(a[x],a[x] + len[x]);
                    tag[x] = 0;
                }
                dark::writelineRange(a[x],a[x] + len[x]);
            }
        }
    }

    return 0;
}