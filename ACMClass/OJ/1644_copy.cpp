#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

char x[104];
vector <char> cur;
struct ez_Q {
    char tot;
    char head;
    char data[102];
    inline void push(char T) {
        data[++tot] = T;
    }
    inline char& front() {
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





inline bool check(char col) {
    for(char i : cur) if(i == col) return true;
    return false;
}

inline void read(char &n) {
    static char ch ;
    ch = getchar();
    while(!isdigit(ch)) {
        ch = getchar();
    } 
    while(isdigit(ch)) {
        n = (n<<1) + (n<<3) + (ch^'0');
        ch = getchar();
    }
}

int main() {
    char k,n;
    read(k);
    read(n);
    cur.reserve(k);
    for(char i = 0 ; i < n  ; ++i) {
        read(x[i]);
        v[x[i]].push(i);
    }
    for(char i = 1 ; i <=20 ; ++i) v[i].push(104);
    int ans = 0;
    for(char i = 0 ; i < n ; ++i) {
        v[x[i]].pop();
        if(check(x[i])) continue;
        if(char(cur.size()) < k) cur.push_back(x[i]);//´æÑÕÉ«
        else {
            ++ans;
            char loc,mxn = 0;
            for(char j = 0 ; j < k ; ++j) {
                if(v[cur[j]].front() > mxn) {
                    mxn = v[cur[j]].front();
                    loc = j;
                }
            }
            cur[loc] = x[i]; 
        }
    }
    printf("%d",int(ans));
    return 0;
}