#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 882377;
const int N = 1e4+8;

int mp[256];
void prework() {
    for(int i = '0' ; i <= '9'; ++i) mp[i] = i-'0'+1;
    for(int i = 'A' ; i <= 'Z'; ++i) mp[i] = i-'A'+11; 
    for(int i = 'a' ; i <= 'z'; ++i) mp[i] = i-'a'+37; 
}

struct hashtable {
    int head[M],tot = 0;
    struct edge{
        int to,nxt;
    }e[N+M];
    string p[N<<1];
    int cnt=0;
    inline int getHash(const string &str) const{
        int ans = 0;
        for(auto i : str) {
            ans = (ans * 71 + mp[int(i)]) % M;
        }
        return ans;
    }
    inline bool insert(const string &str) {
        int tmp = getHash(str);
        //cout << tmp <<endl;
        for(int i = head[tmp]; ;i = e[i].nxt) {
            int v = e[i].to;
            if(p[v] == str) return false;
            if(!e[i].nxt) {//插入成功
                e[i].nxt = ++tot;//开边
                e[i].to  = ++cnt;//开串
                p[cnt]   = str;
                return true;
            }
        }
    }
    inline hashtable() {
        prework();
        for(int i = 0 ; i < M; ++i) {
            head[i]  = i;
//            e[i].nxt = 0;
//            e[i].to  = 0;          
        }
        cnt = 0;
        tot = 0;
    }
}m;

#define endl '\n'


int main() {
    ios::sync_with_stdio(false);
    string str;
    str.reserve(1504);
    int n ;
    cin >> n ;
    int ans = 0;
    //m.initialize();
    while(n--) {
        cin >> str;
        if(m.insert(str)) ++ans;
        //cout << ans << endl;
    }
    cout << ans << endl;
    return 0;
}