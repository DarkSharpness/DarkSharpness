#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1007;
int f[N];

// Get the ancestor.
int get(int x) {
    return f[x] != x ? f[x] = get(f[x]) : x;
}

// Generate a tree.
void generate(vector <int> &v) {
    if(v.empty()) return;
    std::random_shuffle(v.begin(),v.end());
    f[v[0]] = 0;
    for(size_t i = 1 ; i != v.size() ; ++i)
        f[v[i]] = v[rand() % i];
}

// Split n numbers evenly.
std::vector <int> split(int n,int m) {
    vector <int> ans;
    ans.reserve(m + 1);
    for(int i = 0 ; i < m ; ++i)
        ans.push_back((n / m) * i);
    ans.push_back(n);
    return ans;
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = i * i * 10;
        const int m = n;
        int cnt = rand() % (i + 1) + 1;
        auto vec = split(n,cnt);
        std::vector <int> tmp;
        for(int i = 0 ; i != cnt ; ++i) {
            tmp.clear();
            tmp.reserve(i);
            for(int j = vec[i] ; j != vec[i + 1] ; ++j)
                tmp.push_back(j + 1);
            generate(tmp);
        }
        std::vector <int> ttt;
        ttt.resize(m);
        tmp.resize(m);
        for(int i = 0 ; i < m ; ++i) {
            ttt[i] = rand() % n + 1;
            tmp[i] = rand() % n + 1;
        }
        freopen(in.data(),"w",stdout);
        dark::writeline(n,m);
        for(int i = 1 ; i <= n ; ++i)
            dark::writeline(f[i]);
        for(int i = 0 ; i < m ; ++i)
            dark::writeline(tmp[i],ttt[i]);

        freopen(out.data(),"w",stdout);
        for(int i = 1 ; i <= n ; ++i)
            if(!f[i]) f[i] = i;
        for(int i = 1 ; i <= n ; ++i)
            get(i);
        for(int i = 0 ; i < m ; ++i)
            if(f[tmp[i]] == f[ttt[i]])
                puts("Yes");
            else
                puts("No");
    }
    return 0;
}