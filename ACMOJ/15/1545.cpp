#include <iostream>
#include <Dark/inout>

inline int lowbit(int x) { return x & (-x); }

int n,m;
const int N = 3003;
long long c[N][N];

inline void add(int x,int y,int num) {
    for(int i = x; i <= n ; i += lowbit(i))
        for(int j = y ; j <= m ; j += lowbit(j))
            c[i][j] += num;
}

inline long long sum(int x,int y) {
    long long ans = 0;
    for(int i = x; i ; i ^= lowbit(i))
        for(int j = y ; j ; j ^= lowbit(j))
            ans += c[i][j];
    return ans;
}

inline int query(int x,int y,int a) 
{ return sum(x,y) - sum(x - a,y) - sum(x,y - a) + sum(x - a,y - a); }

void build() {
    for(int i = 1; i <= n; ++i) {
        if(i + lowbit(i) <= n) {
            for(int j = 1 ; j <= m ; ++j) {
                if(j + lowbit(j) <= m)
                    c[i + lowbit(i)][j + lowbit(j)] += c[i][j];
            }
        }
    }
}

inline bool is_c(char c) { return c == EOF || c == '1' || c == '2'; }
char &read_opt(char &__c) { while(!is_c(__c = getchar())); return __c; }


signed main() {
    dark::read_u(n,m);
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j)
            dark::read(c[i][j]);
    build();
    char opt;
    int x,y,a;
    while(read_opt(opt) != EOF) {
        dark::read_u(x,y,a);
        if(opt == '1') {
            add(y,x,a);
        } else {
            dark::writeline(query(y,x,a + 1));
        }
    }
    return 0;
}