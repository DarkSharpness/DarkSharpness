#include<bits/stdc++.h>
//快速读入
int read() {
    static int  tmp ;
    static char ch  ;
    tmp  = 0;  
    ch   = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        tmp = tmp * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return tmp;
}

const int N = 1e7;
int a[N+4];

int main() {
    int n,k,ans = 0;
    n =  read();
    k = -read() -1 +read();
    //write(k);
    for(int i = 1; i <= n; ++i) {
        ++a[read()];
    
    }
    for(int i = 0; i <= N; ++i){
        if(!a[i]) continue;
        if(k >= a[i]*i) {
            k -= a[i]*i;
            ans += a[i];
        }
        else {
            ans += k/i;
            break;
        }
    } 
    //write(ans);
    n = ((100.0/n)*(0.9*ans+0.1*n));
    if(n == 100) {printf("100");}
    else {
        k = n/10;
        putchar(k^'0');
        putchar((n-k*10)^'0');
    }
    return 0;
}