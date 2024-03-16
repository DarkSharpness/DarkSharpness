#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
#define endl '\n'
const int N = 1e5 + 10;
struct edge{
    int u,v;
    edge(int U,int V) : u(U),v(V) {
    }
    edge() {
    }
}e[N];
struct query{
    int x,y,z,i;
    query(int X,int Y,int Z,int I) : x(X),y(Y),z(Z),i(I){
    } 
    query() {
    }
};

vector <query> qq;
int n,m,Q,ans[N];

int sz[N],anc[N];
inline void Find(int &x) {
    while(x != anc[x]) {x = anc[x];}
}

vector <edge> history;
inline void Merge(int x,int y) {
    Find(x);
    Find(y);
    if(x == y) return;
    if(sz[x] > sz[y]) swap(x,y);
    // Now sz[y] >= sz[x]

    sz[y] += sz[x];
    anc[x] = y;
    history.emplace_back(x,y);
}

void solve(int l,int r,const vector <query> &q) {
    if(q.empty()) {return;}
    if(l == r) {
        for(int i = 0 ; i != (int)q.size() ; ++i) {
            ans[q[i].i] = l;
        }
        return;
    }
    const int mid = (l+r) >> 1;
    const int cnt = history.size();
    for(int i = l; i <= mid ; ++i) {
        Merge(e[i].u,e[i].v);
    }
    vector <query> L;
    vector <query> R;
    for(int i = 0,x,y ; i != (int)q.size() ; ++i) {
        Find(x = q[i].x);
        Find(y = q[i].y);
        int siz = (x == y ? sz[x] : sz[x] + sz[y]);
        if(siz >= q[i].z) {
            L.push_back(q[i]);
        } else {R.push_back(q[i]);}
    }
    solve(mid+1,r,R);
    for(int i = history.size() - 1,x,y; i >= cnt ; --i) {
        y = history[i].v;
        x = history[i].u;
        anc[x] = x;
        sz[y] -= sz[x];
        history.pop_back();
    }
    solve(l,mid,L);
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i) {
        cin >> e[i].u >> e[i].v;
    }
    cin >> Q;
    qq.reserve(Q);
    for(int i = 0 ; i < Q ; ++i) {
        int x,y,z;
        cin >> x >> y >> z;
        qq.emplace_back(x,y,z,i);    
    }
    for(int i = 1 ; i <= n ; ++i) {
        sz[i] = 1 ; anc[i] = i;
    }

    solve(1,m,qq);

    for(int i = 0 ; i < Q ; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}