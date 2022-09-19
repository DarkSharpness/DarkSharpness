#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

char ch[12];
int cnt;
inline void read(int &tmp) {
    tmp  = 0;  
    ch[0]= getchar();
    while(!isdigit(ch[0])) {
        ch[0] = getchar();
    }
    while(isdigit(ch[0])) {
        tmp = tmp * 10 + (ch[0] ^ '0');
        ch[0]  = getchar();
    }
    //return tmp;
}

inline void write(int tmp) {
    //cnt = 0;
    while(tmp) {
        ch[++cnt] = tmp % 10;
        tmp /= 10;
    }
    while(cnt) {
        putchar(ch[cnt] ^ 48);
        --cnt;
    }
    //putchar('\n');
    puts("");
}


void readchar(char &c) {
    c = getchar();
    while(c!='P'&&c!='N') c = getchar();
}
void readopt (char &c) {
    c = getchar();
    while(!isdigit(c)) c = getchar();
}
const int N = 6e6 + 2;
int pre[N];
int suc[N];
int a[N];
int i,maxn;

int main() {
    int n,q;
    read(n);
    for(i = 1; i <= n; ++i) {
        read(a[i]);
        pre[i] = i-1;
        suc[i] = i+1;
    };
    read(q);
    maxn = n ;
    pre[1] = maxn;
    suc[maxn] = 1;
    sort(a+1,a+n+1);
    char opt;
    while(q--) {
        readopt(opt);
        switch(opt) {
            case '0':
                read(i);
                if(!pre[i]) break;
                if(i == maxn) {
                    if(pre[i] == i) maxn = 0;
                    else maxn = pre[i];
                }
                suc[pre[i]] = suc[i];
                pre[suc[i]] = pre[i];
                pre[i] = 0;
                break;
            case '1':
                readchar(opt);
                read(i);
                if(opt == 'P') {
                    if(!pre[i]) {
                        puts("Invalid.");
                        break;
                    } 
                    write(pre[i]);
                } else {
                    if(!pre[i]) {
                        puts("Invalid.");
                        break;
                    } 
                    write(suc[i]);
                }
                break;
            default:
                if(!maxn) puts("Invalid.");
                else write(a[maxn]);
                break;
        }
    }
    return 0;
}