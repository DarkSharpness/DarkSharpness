#include <iostream>
#include <Dark/inout>

int g[202][202][1002];
int v[202][202][1002];
int r,c,m;


int brute_force() {
    int maxn = 0;
    for(int i = 1 ; i <= r ; ++i)
        for(int j = 1 ; j <= c ; ++j) {
            int t;
            maxn = std::max(maxn,dark::read(t));
            g[i][j][t] += t;
            ++v[i][j][t];
        }
    for(int l = maxn ; l >= 1 ; --l)
        for(int i = 1 ; i <= r ; ++i)
            for(int j = 1 ; j <= c ; ++j)
                g[i][j][l] += g[i - 1][j][l] + g[i][j - 1][l]
                            - g[i - 1][j - 1][l],
                v[i][j][l] += v[i - 1][j][l] + v[i][j - 1][l]
                            - v[i - 1][j - 1][l];

    for(int i = 1 ; i <= r ; ++i)
        for(int j = 1 ; j <= c ; ++j)
            for(int l = maxn ; l >= 1 ; --l)
                g[i][j][l] += g[i][j][l + 1],
                v[i][j][l] += v[i][j][l + 1];
    while(m--) {
        int a,b,c,d,h;
        dark::read(a,b,c,d,h); --a,--b;
        if(g[c][d][1] - g[a][d][1] - g[c][b][1] + g[a][b][1] < h) puts("Impossible");
        else {
            int l = 1;
            int r = maxn + 1;
            while(l != r) {
                int mid = (l + r) >> 1;
                int tmp = g[c][d][mid] - g[a][d][mid] - g[c][b][mid] + g[a][b][mid];
                if(tmp < h) r = mid;
                else l = mid + 1;
            } /* Now f(l) < h , f(l - 1) >= h */
            --l;
            int ret = (g[c][d][l] - g[a][d][l] - g[c][b][l] + g[a][b][l] - h) / l;
            dark::writeline(v[c][d][l] - v[a][d][l] - v[c][b][l] + v[a][b][l] - ret);
        }
    }
    return 0;
}

constexpr int N = 5e5 + 7;

struct node { int ls,rs,cnt,sum; } t[N * 20];

int tot = 0;
int build(int l,int r) {
    int root = ++tot;
    if(l == r) return root;
    int mid = (l + r) >> 1;
    t[root].ls = build( l , mid );
    t[root].rs = build(mid + 1,r);
    return root;
}

int update(int id,int l,int r,int loc) {
    int root = ++tot;
    t[root] = t[id]; 
    t[root].cnt += 1;
    t[root].sum += loc;
    if(l == r) return root;
    int mid = (l + r) >> 1;
    if(loc <= mid) t[root].ls = update(t[root].ls, l , mid ,loc);
    else           t[root].rs = update(t[root].rs,mid + 1,r,loc);
    return root;
}

/* Prefix sum of [1,target] in [L,R] larger than h. */
int query(int L,int R,int l,int r,int h) {
    int ans = 0;
    while(l != r) {
        int sum = t[t[R].ls].sum - t[t[L].ls].sum;
        int cnt = t[t[R].ls].cnt - t[t[L].ls].cnt;
        int mid = (l + r) >> 1;
        if(sum > h) L = t[L].ls , R = t[R].ls , r = mid;
        else if(sum == h) return ans + cnt;
        else        L = t[L].rs , R = t[R].rs , l = mid + 1,
                    h -= sum , ans += cnt;
    } /* Now l == r && h > 0 */
    return ans + h / r;
}

int a[N];
int rt[N];

signed main() {
    dark::read(r,c,m);
    if(r != 1) return brute_force();
    int maxn = 0;
    for(int i = 1 ; i <= c ; ++i)
        if(dark::read(a[i]) > maxn) maxn = a[i];

    rt[0] = build(1,maxn);

    for(int i = 1 ; i <= c ; ++i)
        rt[i] = update(rt[i - 1],1,maxn,a[i]); 

    while(m--) {
        int l,r,h;
        dark::read(l,l,r,r,h); --l;
        int sum = t[rt[r]].sum - t[rt[l]].sum;
        if(sum < h) puts("Impossible");
        else {
            dark::writeline(t[rt[r]].cnt - t[rt[l]].cnt - 
                            query(rt[l],rt[r],1,maxn,sum - h));
        }
    }
    return 0;
}