#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr short N = 5008;
vector <int> g[N];

short anc[N]; //father of id
short dep[N]; //depth  of id         /// Root depth = 0
short len[N]; //longest line   of id /// At least 1, dot number
short maxn[N];//maximum length of id /// At least 1, dot number
short len1[N],
    len2[N],
    len3[N];

inline void read(short &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

#define max(_A,_B) ( _A > _B ? _A : _B )
inline void dfs0(short id) {
    maxn[id] = 1;
    for(short to : g[id]) {
        if(to == anc[id]) continue;
        anc[to] = id;
        dep[to] = dep[id] + 1;
        dfs0(to); 
        if(len[to] >= len1[id]) {
            len3[id] = len2[id];
            len2[id] = len1[id];
            len1[id] = len[to];
        } else if(len[to] >= len2[id]) {
            len3[id] = len2[id];
            len2[id] = len[to];
        } else if(len2[to] > len3[id]) {
            len3[id] = len[to];
        }
        if(maxn[to] > maxn[id]) maxn[id] = maxn[to];
    }
    len[id]  = len1[id]+1;
    maxn[id] = max(maxn[id],len1[id]+len2[id]+1);
    //cout << id << " "<< len1[id] << " " << len2[id] << " " 
    //    << len3[id] << " " << anc[id]  << " " << maxn[id] << endl;
}

short ans;
multiset <short> s; //maximum length
multiset <short> l; //maximum line-length

void dfs1(short id) {
    //cout << id << endl;
    if(id != 1) {//count thy answer
        ans = max(ans,(maxn[id]-1) * (*s.crbegin()-1) );
    }
    auto it = s.begin();
    short longest = *l.crbegin();
    for(short to : g[id]) {
        if(to == anc[id]) continue;
        s.insert(max(maxn[to],
                     longest + len[to] + dep[to]));
    }
    for(short to : g[id]) {
        if(to == anc[id]) continue;
        l.insert(len[to]-dep[id]);
    }
    if(g[id].size() == 2) { // 1 is father only
        s.insert(longest + dep[id] + 1);//null node
    }
    s.insert(len1[id] + len2[id] + 1);

    //dfs1
    for(short to : g[id]) {
        if(to == anc[id]) continue;
        
        if(len[to] == len1[id]) {
            it = s.find(len1[id]+len2[id]+1);
            s.erase(it);
            s.insert(len2[id] + len3[id] + 1);
        } else if(len[to] == len2[id]) {
            it = s.find(len1[id] + len2[id] + 1);
            s.erase(it);
            s.insert(len1[id] + len3[id] + 1);
        } 

        it = s.find(max(maxn[to],longest + len[to] + dep[to]));
        s.erase(it);
        it = l.find(len[to]-dep[id]);
        l.erase(it);

        dfs1(to);

        s.insert(max(maxn[to],longest + len[to] + dep[to]));
        l.insert(len[to]-dep[id]);
        if(len[to] == len1[id]) {
            it = s.find(len2[id] + len3[id] + 1);
            s.erase(it);
            s.insert(len1[id] + len2[id] + 1);
        } else if(len[to] == len2[id]) {
            it = s.find(len1[id] + len3[id] + 1);
            s.erase(it);
            s.insert(len1[id] + len2[id] + 1);
        } 

    }

    it = s.find(len1[id] + len2[id] + 1);
    s.erase(it);
    if(g[id].size() == 2) { // 1 is father only
        it = s.find(longest + dep[id] + 1);
        s.erase(it);
    }
    
    for(short to : g[id]) {
        if(to == anc[id]) continue;
        it = s.find(max(maxn[to],
                     longest + len[to] + dep[to]));
        s.erase(it);
    }
    for(short to : g[id]) {
        if(to == anc[id]) continue;
        it = l.find(len[to]-dep[id]);
        l.erase(it);
    }

}


int main() {
    short n;
    read(n);
    for(short i = 1,x,y; i < n ; ++i) {
        read(x);
        read(y);
        g[x].push_back(y);
        g[y].push_back(x);
    }    
    g[1].push_back(0);
    anc[1] = 0;
    l.insert(0);
    dfs0(1);
    dfs1(1);
    printf("%d",ans);
    return 0;
}
