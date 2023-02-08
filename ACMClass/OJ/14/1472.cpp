#include <bits/stdc++.h>
#include <Dark/inout>
#include <Dark/include/basic.h>


namespace dark {
/**
 * @brief Fast built-in LOG2 function from
 * "骆可强《论程序底层优化的一些方法与技巧".
 * You can access that at 
 * https://github.com/lzyrapx/Competitive-Programming-Docs/.
 * 
 * 
 * @return log2(x) in 32-bit. Note that log2(0) will return 0;
 */
inline unsigned int LOG2(unsigned x){
    unsigned ret = 0;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}

}

const int N = 5e5 + 1;
int w[N];       // width
int Log[N];
int idx[20][N]; // Index of smallest in [j,j + 2 ^ i)

void prework(int n) {
    for(int i = 1 ; i <= n ; ++i) Log[i] = dark::LOG2(i);
    for(int j = 1 ; j <= n ; ++j) idx[0][j] = j;
    for(int i = 1,len = 2; len <= n ; ++i,len <<= 1) {
        for(int j = 1 ; j + len <= n ; ++j) {
            idx[i][j] = w[idx[i - 1][j]] > w[idx[i - 1][j + (len >> 1)]] 
                        ?
                        idx[i - 1][j + (len >> 1)] : idx[i - 1][j];
        }
    }
}



/* Find the index.  */
int query(int l,int r,int k) {
    
}


signed main() {
    int n = dark::read_u(n);
    dark::readRange(w + 1,n);
    int m = dark::read_u(m);
    prework(n);
    int l,r,k;
    while(m--) {
        dark::read_u(l,r,k);
        dark::writeline(w[query(l,r,k)]);
    }
    return 0;
}