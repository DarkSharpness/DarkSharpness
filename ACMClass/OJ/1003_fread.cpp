#include<bits/stdc++.h>
char ch[10]; 
const int N = 2e7+2;
char in[N<<1],*x=in,*y=in;
bool flag;

inline char read() {
    if(x==y&&
        (y = ( x = in)+fread(in,1,N,stdin),
        x==y) ){
        return EOF;
    }
    else return *x++;
}
int tmp;

inline int FFread() {
    tmp  = 0;
    flag = true;
    ch[0] = read();
    while(ch[0] < '0' || ch[0] > '9'){
        if(ch[0] == '-') flag = false;
        ch[0] = read();
    }
    while(ch[0] >= '0'&&ch[0] <= '9') {//????????
        tmp = (tmp<<1) + (tmp<<3) + (ch[0] ^ '0');
        ch[0] = read();
    }
    return flag ?  tmp : -tmp;
}

int a[N+4];

int main() {
    int n,k,ans = 0;
    n=FFread();
    k=-FFread()-1+FFread();
    //write(k);
    for(int i = 1; i <=n; ++i) 
        ++a[FFread()];
    for(int i = 0; i <=N; ++i){
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