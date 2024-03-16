#include <bits/stdc++.h>
// #include <Dark/inout>

const int N = 3e5 + 3;
int u[N];
int cnt;
int ans = -1;

int anc[N];
int siz[N];

int find(int x) {
    return anc[x] ? anc[x] = find(anc[x]) : x;
}

// Work out the answer for the first time.
void work() {

}

/* Modify the answer in the set x. */
void modify(int xx,int x,int y,int z) {
    
}

void link(int x,int y,int z) {
    int xx = find(x);
    int yy = find(y);
    if(xx != yy) {

        if(1 & siz[xx] & siz[yy])
            if(!--cnt) // cnt = 0. Work out the answer.
                work();


        anc[yy] = xx;
        siz[xx] += siz[yy];
        return;
    }
    // From the same set case.

    modify(xx,x,y,z);



}

signed main() {
    int n,m;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    if(n % 2 == 1) {
        for(int i = 0 ; i < m ; ++i) {
            int x,y,z;
            std::cin >> x >> y >> z;
        }
        for(int i = 0 ; i < m ; ++i)
            std::cout << "-1\n";
        return 0;
    }
    cnt = n >> 1;
    for(int i = 1 ; i <= n ; ++i) siz[i] = 1;
    for(int i = 0 ; i < m ; ++i) {
        int x,y,z;
        std::cin >> x >> y >> z;
        link(x,y,z);
        std::cout << ans << '\n';
    }

    return 0;
}