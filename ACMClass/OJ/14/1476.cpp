#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 8;
const int Q = 1e6 + 8;


void Fread(int &tmp) {
    char ch;
    bool flag = false;
    while(!isdigit(ch = getchar())) if(ch == '-') flag = true;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
    if(flag) tmp = -tmp;
}

void write(int x) {
    if(!x) return (void) puts("0");
    static char ch[12] = "";
    int top = 11;
    while(x) {
        ch[--top] = (x % 10) ^ '0';
        x /= 10;
    }
    puts(ch + top);
}

void read() {}

template <class Integer,class ...Integers>
void read(Integer &arg,Integers &...args) {
    Fread(arg);
    return read(args...);
}

inline int max(int x,int y) { return x > y ? x : y; }
inline int min(int x,int y) { return x < y ? x : y; }

inline unsigned int LOG2(unsigned x){
    unsigned ret = 0;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}
int n,q;
int a[N];
int minn[18][N],maxn[18][N];
int Log2[N];

#define qmax max(maxn[i][l],maxn[i][r - (1 << i) + 1]) // Require i = log2[r - l]
#define qmin min(minn[i][l],minn[i][r - (1 << i) + 1]) // Require i = log2[r - l]

signed main() {
    read(n,q);
    for(int i = 1 ; i <= n ; ++i) {
        read(a[i]);
    }
    for(int i = 1,j ; i <= n ; ++i) {
        j = 0;
        read(j); // b[i]
        minn[0][i] = maxn[0][i] = (a[i] += a[i-1] - j); // Prefix sum of a[i] + b[i]
    }
    // for(int i = 1 ; i <= n ; ++i) std::cout << a[i] << ' ';puts("");
    for(int i = 1,len ; (len = 1 << i) <= n + 1 ; ++i) {
        for(int l = 0; l + len - 1 <= n ; ++l) { // Using cache optimization
            minn[i][l] = min(minn[i - 1][l],minn[i - 1][l + (len >> 1)]);
            maxn[i][l] = max(maxn[i - 1][l],maxn[i - 1][l + (len >> 1)]);
        }
    }
    for(int i = 2 ; i <= n ; ++i) Log2[i] = Log2[i >> 1] + 1;
    while(q--) {
        int l = 0,r = 0;
        read(l,r); --l;
        int i = Log2[r - l];
        if(a[l] != a[r] || qmax > a[l]) puts("-1");
        else write(a[r] - qmin);
    }
    return 0;
}
