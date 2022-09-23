#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int x[100];



struct ez_Q {
    int tot;
    int head;
    int data[102];
    inline void push(int T) {
        data[++tot] = T;
    }
    inline int& front() {
        return data[head];
    }
    inline void pop() {
        ++head;
    }
    ez_Q() {
        tot  = 0;
        head = 1;
    }
}v[24];

vector <int> cur(102);

inline bool check(int col) {
    for(int i : cur) if(i == col) return true;
    return false;
}

inline void read(int &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch = getchar();
    }
}
char ch[2];

int main() {
    int k,n;
    cur.resize(0);
    read(k);
    read(n);
    for(int i = 0 ; i < n  ; ++i) {
        read(x[i]);
        v[x[i]].push(i);
    }
    for(int i = 1 ; i <=20 ; ++i) v[i].push(114514);
    int ans = 0;
    for(int i = 0 ; i < n ; ++i) {
        v[x[i]].pop();
        if(check(x[i])) continue;
        if(int(cur.size()) < k) cur.push_back(x[i]);//´æÑÕÉ«
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
    printf("%d",ans);
    return 0;
}