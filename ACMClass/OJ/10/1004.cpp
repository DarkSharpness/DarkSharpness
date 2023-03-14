#include<bits/stdc++.h>
using namespace std;

constexpr int N = 1<<17;
int a[N];
int t[N];

struct Tarray {
    static inline int lowbit(int x) { return x & (-x); }
    #define maxn (N)
    inline void add(int loc) {
        while(loc < maxn) {
            ++t[loc];
            loc += lowbit(loc);
        }
    }
    //查询val的最大排名
    inline int getrank(int val) {
        int ans = 0;
        while(val) {
            ans += t[val];
            val -= lowbit(val);
        } 
        return ans;
    }

    //排名为rk的值,如果超过最大rk就是最大
    int getval(int rk) {
        unsigned int now = 0;
        for(int i = 16; ~i; --i) {
            now |= (1 << i);
            if(now >= maxn || t[now] >= rk) now ^= (1 << i);
            else rk -= t[now];
        }
        return now + 1;
    }

    int query(int val,int n) {
        int rk = getrank(val);
        if(!rk) {
            return getval(1) - val; 
        } else {
            int val1 = getval(rk);
            if(val == val1) return 0;
            if(rk == n-1) return val - val1;
            else 
            {
                int val2 = getval(rk+1);
                return (val1 + val2 < val << 1) ?
                        val2 - val : val - val1;
            }
        }
    }
    inline void initialize() {
        memset(t,0,sizeof(t));
    }
    Tarray() = default;
}A;

void read(int & tmp) {
    char ch  ;
    tmp  = 0;  
    ch   = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        tmp = (tmp << 1) + (tmp << 3) + (ch ^ '0');
        ch  = getchar();
    }
}

char ch[20];  
int  cnt;

void write(int x) {
    if(!x) {putchar('0'),putchar('\n');return;}
    cnt = -1;
    while(x) {
        ch[++cnt] = (x % 10) ^ '0';
        x /= 10;
    }
    while(cnt != -1) {
        putchar(ch[cnt]);
        --cnt;
    }
    putchar('\n');
}


int main() {
    int T,n,ans=0;
    read(T);
    while(T--) {
        read(n);
        for(int i = 1; i <= n; ++i) 
            read(a[i]),++a[i];
        ans += a[1] - 1;
        A.add(a[1]);
        for(int i = 2; i <= n; ++i) {
            ans += A.query(a[i],i);
            A.add(a[i]);
        }
        write(ans);
        if(T) A.initialize(),ans = 0;
    }
    return 0;
}
