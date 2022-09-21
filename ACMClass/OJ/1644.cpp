#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int x[100];
queue <int> v[100];
vector <int> cur;

inline bool check(int col) {
    for(int i : cur) if(i == col) return true;
    return false;
}


int main() {
    ios::sync_with_stdio(false);
    #define endl '\n'
    int k,n;
    cin >> k >> n ;
    for(int i = 0 ; i < n  ; ++i) cin >> x[i],v[x[i]].push(i);
    for(int i = 1 ; i <=20 ; ++i) v[i].push(114514);
    //v[0].push(0);
    int ans = 0;
    for(int i = 0 ; i < n ; ++i) {
        v[x[i]].pop();
        if(check(x[i])) continue;
        if(int(cur.size()) < k) cur.push_back(x[i]);//???
        else { //cur.size() == k
            ++ans;
            int loc,mxn = 0;
            for(int j = 0 ; j < k ; ++j) {
                if(v[cur[j]].front() > mxn) {
                    mxn = v[cur[j]].front();
                    loc = j;
                }
            }
            cur[loc] = x[i]; 
        }
    }
    cout << ans << endl;
    return 0;
}