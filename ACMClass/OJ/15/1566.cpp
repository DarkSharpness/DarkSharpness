#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


inline void read(int &tmp) {
    tmp = 0;
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while( isdigit(ch)) {
        tmp = tmp*10 + (ch^'0');
        ch = getchar();
    }
}
constexpr int N = 2e6+4;
unordered_map <int,int> mp(N);
pair <int,int> p[N];
int anc[N];
int Get(int x) {
    if(anc[x] == x) return x;
    return anc[x] = Get(anc[x]);
}

void merge(int x,int y) {
    int a = Get(x);
    int b = Get(y);
    anc[b] = a; 
}

int cnt;
inline int getHash(const int z) {
    auto it = mp.find(z);
    if(it == mp.end()) {
        ++cnt;          //发现新颜色
        mp[z]    = cnt;
        anc[cnt] = cnt;
        return cnt;
    } else {
        return it->second;
    }
}

int main() {
    int t,n,x,y,z,X,Y,tot;
    read(t);
    while(t) {
        tot = cnt = 0;
        read(n);
        bool flag = true;
        for(int i = 0 ; i < n; ++i) {
            read(x); 
            read(y); 
            read(z);
            if(z) {
                X = getHash(x);
                Y = getHash(y);
                merge(X,Y);
            } else {
                if(flag){
                    if(x == y) tot = flag = false;
                    else p[++tot] = make_pair(x,y);
                }
            }
        }
        while(tot) {          
            auto it1 = mp.find(p[tot].first );
            auto it2 = mp.find(p[tot].second);
            if(it1 != mp.end() && it2 != mp.end() &&
                Get(it1->second) == Get(it2->second)) {
                flag = false;
                break;
            }
            --tot;
        } 
        if(flag) puts("YES");
        else     puts("NO");
        if(--t)  mp.clear();
    }

    return 0;
}
