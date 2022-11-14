#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

const char key[] = {
    '-','<','>',
    '0','1','-',
};
int delta[128];
string func;
map <string,int> mp;
int papers;



inline bool check(char _ch) {
    for(auto _c : key) {
        if(_c == _ch) {
            return true;
        }
    }
    return false;
}



inline char getkey() {
    char _ch = getchar();
    while(!check(_ch)) {
        if(_ch == EOF) {
            puts("End of File ERROR!");
            exit(114514);
        }
        _ch = getchar();
    }
    return _ch;
}

void prework() {
    delta['-'] = 0;
    delta['<'] = -1;
    delta['>'] = 1;
}




signed main() {
    prework();
    cin >> papers;
    return 0;
}