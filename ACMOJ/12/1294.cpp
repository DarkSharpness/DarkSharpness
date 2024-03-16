#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void Fread(unsigned int &tmp) {
    static char ch ;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch = getchar();
    }
}
inline void Fwrite(unsigned int tmp) {
    static char ch[12];
    static int  tot = 0;
    while(tmp) {
        ch[++tot] = (tmp % 10) ^ '0';
        tmp /= 10; 
    }
    while(tot) {
        putchar(ch[tot]);
        --tot;
    }
    putchar('\n');
}
unsigned int T,x,y;


int main() {
    Fread(T);
    while(T--) {
        Fread(x);
        Fread(y);
        Fwrite(x+y);
    }

    return 0;
}