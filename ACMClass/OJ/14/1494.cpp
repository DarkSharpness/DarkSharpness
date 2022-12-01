#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6;
int h[N],l[N];
int st[N],top;
inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^'0');
        ch = getchar();
    }
}

int main() {
    int n;
    int a[N];
    read(n);
    for(int i = 1 ; i <= n ; ++i) {
        read(a[i]);
        while(top && a[i] > a[st[top]]) {
            l[i] = st[top--];
        }
        st[++top] = i;
    }


    return EXIT_SUCCESS;
}