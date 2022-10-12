#include <bits/stdc++.h>
using namespace std;

inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

int n,t;


int main() {
    read(n);
    while(n--) {
        read(t);
        if(t & 1) {
            puts("First");
            return 0;
        }
    }    
    puts("Second");

    return 0;
}