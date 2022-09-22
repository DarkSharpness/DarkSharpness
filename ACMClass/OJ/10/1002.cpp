#include<iostream>

char ch[8];  
char cnt = 0; 
int n,ans = 0,t;

int read(int & tmp) {
    tmp  = 0;  
    ch[0]   = getchar();
    while(ch[0] < '0' || ch[0] > '9') {
        ch[0] = getchar();
    }
    while(ch[0] >= '0'&&ch[0] <= '9') {
        tmp = (tmp<<1) + (tmp<<3) + (ch[0] ^ '0');
        ch[0]  = getchar();
    }
    return tmp;
}


 

int main() {
    read(n);
    while(n--) {
        read(t);
        if(t > ans) ans = t;
    }
    printf("%d",ans);
    return 0;
}