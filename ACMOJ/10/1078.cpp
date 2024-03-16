#include<bits/stdc++.h>
using namespace std;
typedef long long ll;



void empty() {
    static char ch  ;
    ch   = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        ch  = getchar();
    }
}

void read(int & tmp) {
    static char ch  ;
    tmp  = 0;  
    ch   = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        tmp = (tmp << 1) + (tmp << 3) + (ch ^ '0');
        ch  = getchar();
    }
}

char ch[10];  
int  cnt    = -1;  
void write(int x) {
    while(x) {
        ch[++cnt] = (x % 10) ^ '0';
        x /= 10;
    }
    while(cnt != -1) {
        putchar(ch[cnt]);
        --cnt;
    }
}

int n,x,y,ans = 1;
constexpr int N = 1e7;
int a[N];
int main() {
    read(n);
    for(int i = 0 ; i != n ; ++i) {
        empty();
        read(a[i]);
    }
    int last = a[n-1];
    for(int i = n-2 ; i != - 1; --i) {
        if(last < a[i]) continue; 
        last = a[i];
        ++ans;
    }
    printf("%d",ans);
    return 0;
}