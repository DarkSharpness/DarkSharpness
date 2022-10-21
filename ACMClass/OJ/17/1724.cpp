#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 1e5 + 8;
int n,m;
int a[N];
int maxn[N],minn[N];

struct node {
    int ls,rs;
    int val;  //maximum
}t[1919810 << 2];
int tot;
inline int check(int &id) {
    return id ? id : id = ++tot;
}


#define ls t[id].ls
#define rs t[id].rs
inline int lowbit(int x) {
    return x & (-x);
}


#define mid ((l+r)>>1)



// insert at loc
inline void update(int id,int l,int r,int loc,int val) {
    while(1) {
        t[id].val = max(t[id].val,val);
        if(l == r) break;
        if(loc <= mid) {
            id = check(ls);
            r = mid;
        }
        else {
            id = check(rs);
            l = mid + 1;
        }
    }
}

int query(int id,int l,int r,const int R) {
    int ans = 0;
    while(1) {
        while(id && l != r && R <= mid) {
            // go leftward
            r = mid;
            id = ls;
        }
        if(!id)    return ans; //empty node
        //R == r : target node
        if(R == r) return max(ans,t[id].val);
        //R > mid: ans = leftans
        ans = max(ans,t[ls].val);
        l = mid + 1;
        id = rs;
    }
}   


inline void insert(int x,int y,int val) {
    while(x <= n) {
        update(x,1,n,y,val);
        x += lowbit(x);
    }
}

inline int query(int x,int y) {
    int ans = 0;
    while(x) {
        ans = max(ans,query(x,1,n,y));
        x ^= lowbit(x);
    }
    return ans;
}

inline void read(int &tmp) {
    char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}


signed main() {
    read(n);
    read(m);
    tot = n;
    for(int i = 1,x ; i <= n ; ++i) {
        read(x);
        a[i] = maxn[i] = minn[i] = x;
    }
    for(int i = 1,x,y; i <= m ; ++i) {
        read(x);
        read(y);
        maxn[x] = max(maxn[x],y);
        minn[x] = min(minn[x],y);
    }
    int ans = 0,tmp = 0;
    for(int i = 1 ; i <= n ; ++i) {
        tmp = query(a[i],minn[i]) + 1;
        ans = max(tmp,ans);
        insert(maxn[i],a[i],tmp);
    }
    printf("%d",ans);

    return 0;
}