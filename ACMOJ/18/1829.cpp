#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 303;
const int S = N / M + 9;
pair <int,int> t[N];
inline int& c(int i) { return t[i].second; }
inline int& x(int i) { return t[i].first;  }
int cnt[N];
int id[N],tot;
int near[S];
int f[S][N];
vector <int> loc[N];

signed main() {
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    int maxc = 0;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> x(i) >> c(i);
        if(++cnt[c(i)] == M) id[c(i)] = ++tot;
        maxc = max(maxc,c(i));
    }

    for(int i = 1 ; i <= tot ; ++i)
        memset(f[i],63,sizeof(int) * (maxc + 1));

    sort(t + 1,t + n + 1);
    for(int i = 1 ; i <= tot ; ++i) near[i] = -1e8 - 9;
    for(int i = 1 ; i <= n ; ++i) {
        if(id[c(i)]) near[id[c(i)]] = x(i);
        else loc[c(i)].push_back(x(i));
        for(int j = 1 ; j <= tot ; ++j)
            f[j][c(i)] = min(f[j][c(i)],x(i) - near[j]);
    }

    for(int i = 1 ; i <= tot ; ++i) near[i] = 2e8 + 9;
    for(int i = n ; i >= 1 ; --i) {
        if(id[c(i)]) near[id[c(i)]] = x(i);
        for(int j = 1 ; j <= tot ; ++j)
            f[j][c(i)] = min(f[j][c(i)],near[j] - x(i));
    }

    int lastans = 0;
    while(m--) {
        int a,b;
        cin >> a >> b;
        a ^= lastans;
        b ^= lastans;
        if(!cnt[a] || !cnt[b]) {
            cout << "invalid\n";
            lastans = 0;
            continue;
        }
        if(cnt[a] < M && cnt[b] < M) {
            auto i = loc[a].begin(),j = loc[b].begin();
            lastans = abs(*i - *j);
            while(i != loc[a].end() && j != loc[b].end()) {
                lastans = min(lastans,abs(*i - *j));
                *i < *j ? ++i : ++j;
            }
        } else {
            if(cnt[a] < M) swap(a,b);
            lastans = f[id[a]][b];
        }
        cout << lastans << '\n';
    }
    return 0;
}
