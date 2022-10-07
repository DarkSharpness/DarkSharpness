#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6;
inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp =  tmp * 10 + (ch ^ '0');
        ch  = getchar();
    }
}

int a[N],n;
int l[N],r[N];
int st[N],top;
inline void work() {
    for(int i = 0 ; i < n ; ++i) {
        while(top && a[i] > a[st[top]]) {
            r[st[top--]] = i-1;//×îÓÒ¶Ë
        }
        st[++top] = i;
    }
    while(top) {
        r[st[top--]] = n-1;//×îÓÒ¶Ë
    }
    for(int i = n ; i != -1 ; --i) {
        while(top && a[i] > a[st[top]]) {
            l[st[top--]] = i+1;//×î×ó¶Ë
        }
        st[++top] = i;
    }
     while(top) {
        l[st[top--]] = 0;//×î×ó¶Ë
    }
}

int main() {
    read(n);
    for(int i = 0 ; i < n ; ++i)
        read(a[i]);
    work();
    int ans = 0,loc;
    for(int i = 0,c ; i < n ; ++i) {
        c = 0;
        read(c);
        c *= r[i]-l[i]+1;
        if(c > ans) {
            loc = i;
            ans = c;
        }
    }
    printf("%d %d",loc,ans);
    return 0;
}