#include<bits/stdc++.h>
#include <Dark/inout>
using namespace std;
const int N = 1e6+10;
int a[N],n,m;
int tail,head,q[N]; 


void getmin() {
    head = 1 ;
    tail = 0 ;
    for(int i = 1; i <= n; ++i) {
        if(head <= tail && i - q[head] == m) ++head;
        while(head <= tail && a[i] <= a[q[tail]]) --tail;
        q[++tail]=i;
        if(i >= m) dark::write(a[q[head]]),putchar(' ');
    }
}
void getmax() {
    head = 1 ;
    tail = 0 ;
    for(int i = 1; i <= n; ++i) {
        if(head<=tail && i - q[head] == m) ++head;
        while(head <= tail && a[i] >= a[q[tail]]) --tail;
        q[++tail]=i;
        if(i >= m) dark::write(a[q[head]]),putchar(' ');
    }
}

int main() {
    dark::read(n,m);
    for(int i = 1; i <= n ; ++i) dark::read(a[i]);
    getmin();puts("");
    getmax();puts("");
    return 0;
}
