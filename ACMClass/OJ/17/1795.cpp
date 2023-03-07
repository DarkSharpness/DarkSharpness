// A simple hacking code provided by Hastin.

#include <iostream>
using ull = unsigned long long;

const int N = 3e5 + 3;
const ull B = 37;
int top;

std::string str[N];
bool exist[N];
ull hash[N];

inline void gethash(std::string &s) {
    hash[top] = 0;
    for(ull i = 0 ; i != s.length() ; ++i) 
        hash[top] = hash[top] * B + s[i];
}


ull ksm(ull len,ull base = B) {
    ull ans = 1;
    while(len) {
        if(len & 1) ans *= base;
        base *= base;
        len >>= 1;
    }
    return ans;
}

ull work() {
    ull cnt = 0;
    std::string &s = str[top];
    for(int i = 0 ; i != top ; ++i) {
        if(!exist[i] || str[i].length() > s.length()) continue;
        int len = str[i].length();
        ull h = 0;
        for(int j = 0 ; j != len ; ++j) h = h * B + s[j];
        cnt += (h == hash[i]);
        const ull base = ksm(len);
        for(ull j = len ; j != s.length() ; ++j) {
            h = h * B + s[j] - s[j - len] * base;
            cnt += (h == hash[i]);
        }
    }
    return cnt;
}

signed main() {
    std::ios::sync_with_stdio(false);
    int n,m;
    // scanf("%d%d",&n,&m);
    std::cin >> n >> m;
    ull lastans = 0;
    for(int i = 1 ; i <= n ; ++i) {
        int opt;
        // scanf("%d",&opt);
        std::cin >> opt >> str[top];
        if(m) opt ^= lastans;
        if(opt == 1) {
            gethash(str[top]);
            exist[top++] = true;
        } else if(opt == 2) {
            for(int i = 0 ; i != top ; ++i)
                if(str[i] == str[top]) {
                    exist[i] = false;
                    // break;
                }
        } else {
            std::cout << (lastans = work()) << '\n';
        }
    }
    return 0;
}

