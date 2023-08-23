#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

vector <long long> v;
queue <long long> q,t;
vector <long long> ans;
long long bias = 0;

void generate() {
    static int last = 0;
    int temp = 0;
    int type = (rand() % 101) % 4 + 1;
    if(type == 4) {
        if(last == type || t.empty())
            type = (rand() % 8) % 3 + 1;
    }
    if(type == 3 && last == type) type = 2;
    switch(type) {
        case 1:
            bias += (temp = rand() % 51 - 26);
            dark::writeline(type,temp);
            break;
        case 2:
            dark::writeline(type);
            t.push(q.front());
                q.pop();
            break;
        case 3:
            dark::writeline(type);
            while(t.size() && t.front() < q.front() + bias)
                t.pop();
            break;
        case 4:
            dark::writeline(type);
            ans.push_back(t.front());
            break;
        default: exit(1);
    }
    last = type;
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int m = i * i * i * 100 - 90;
        const int n = rand() % (m / 2) + m / 2;
        v.resize(n);
        bias = 0;
        for(int i = 0 ; i < n ; ++i)
            v[i] = (rand() | rand() << 14) % (n << 1) + 1;
        sort(v.begin(),v.end());

        freopen(in.c_str(),"w",stdout);

        dark::writeline(n,m);
        dark::writelineRange(v.begin(),v.end());
        while(q.size()) q.pop();
        while(t.size()) t.pop();
        ans.clear();
        for(int i = 0 ; i < n ; ++i)
            q.push(v[i]);
        for(int i = 0 ; i < m ; ++i)
            generate();

        freopen(out.c_str(),"w",stdout);
        for(auto i : ans) dark::writeline(i);
    }
    return 0;
}