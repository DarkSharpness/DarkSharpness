#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 102;

struct pack { long long x, y; };

pack work(char opt,pack p,pack q) {
    auto [x,y] = p;
    auto [a,b] = q;
    switch(opt) {
        case '-': a = -a; /* 把减法转化为加法 */
        case '+': {
            /* 处理掉分母的负号 */
            if(b < 0) b = -b,a = -a;
            long long c = x * b + y * a,
                        d = b * y;
            long long t = gcd(abs(c),d);
            x = c / t, y = d / t;
            break;
        }
        case '/': swap(a,b); /* 把除法转换为乘法 */
        case '*': {
            /* 处理掉分母的负号 */
            if(b < 0) b = -b,a = -a;
            x *= a , y *= b;
            long long t = gcd(abs(x),y);
            x /= t , y/= t;
            break;
        }
    } return {x,y};
}


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 8 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        int n = rand() % 10 + 4;
        freopen(in.data(),"w",stdout);
        dark::writeline(n + 1);
        long long x = 0,y = 1;
        long long a = rand() % 9 * 2 - 7;
        long long b = 4;
        dark::writeline('+',a,b);
        auto [c,d] = work('+',{x,y},{a,b});
        x = c,y = d;
        while(n--) {
            char opt = rand() + rand() + rand() + rand();
            if     (opt % 4 == 0) opt = '+';
            else if(opt % 4 == 1) opt = '-';
            else if(opt % 4 == 2) opt = '*';
            else opt = '/';  

            long long a = rand() % 30 - 15;
            long long b = rand() % 60 - 6;

            if(rand() % 3 == 2) swap(a,b);
            if(b == 0) b = rand() % 20 + 1;
            if(a == 0 && opt == '/') a = rand() % 10 + 1;

            dark::writeline(opt,a,b);
            auto [c,d] = work(opt,{x,y},{a,b});
            if(max(abs(c),abs(d)) > 2e9) throw;
            x = c,y = d;
        }
        freopen(out.data(),"w",stdout);
        dark::writeline(x,y);
    }
    return 0;
}