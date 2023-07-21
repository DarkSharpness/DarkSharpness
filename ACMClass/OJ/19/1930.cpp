#include <bits/stdc++.h>
// #include <Dark/inout>

const int N = 101;

using heap = std::priority_queue <int>;

int id = 0;
int nxt[N][26];
int siz[N];
int exi[N];
int dep[N];
int len[N];
int loc[N];

auto insert(const char *str) {
    int i = 0;
    for(; *str ; ++str) {
        int &t = nxt[i][*str - 'a'];
        if(!t) {
            t = ++id;
            dep[t] = dep[i] + 1; 
        } ++siz[i = t];
    } exi[i] = 1;
    return str;
}

int sum = 0;

heap dfs(int x) {
    heap ans;
    for(int i = 0 ; i < 26 ; ++i)
        if(nxt[x][i]) {
            heap tmp = dfs(nxt[x][i]);
            while(tmp.size()) {
                ans.push(tmp.top());
                tmp.pop();
            }
        }

    if(exi[x])
       ans.push(dep[x]);
    else {
        auto tmp = ans.top();
        ans.pop();
        sum += tmp - dep[x];
        ans.push(dep[x]);
    }
    return ans;
}

void work() {
    for(int i = 0 ; i < 26 ; ++i)
        if(nxt[0][i]) dfs(nxt[0][i]);
}


char buf[N];

signed main() {
    int n, L = 0;
    std::cin >> n;
    while(n--) {
        std::cin >> buf;
        L += insert(buf) - buf;
    }
    work();
    std::cout << L - sum;
    return 0;
}