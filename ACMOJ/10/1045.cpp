#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


constexpr int N = 1e6+2;
int nxt[N],loc[N],pre[N];
char a[N],b[N];
int len_a,len_b,tot;

void make_nxt() {
    nxt[0] = -1;
    int j  = -1;
    for(int i = 1; i < len_b ; ++i) {
        while(j != -1 && b[i] != b[j+1]) j = nxt[j];
        if(b[i] == b[j+1]) ++j;
        nxt[i] = j;
    } 
}


void censor() {
    int j  = -1;
    loc[0] = -1;
    for(int i = 0; i < len_a ; ++i) {
        loc[++tot] = i;
        while(j != -1 && a[i] != b[j+1]) j = nxt[j];
        if(a[i] == b[j+1]) ++j;
        if(j == len_b-1) {
            tot -= len_b;
            j = (loc[tot]==-1) ? -1 : pre[loc[tot]];
        }
        pre[i] = j;
    } 
}


void read(char *c,int &len) {
    len = -1;
    while((c[++len] = getchar()) <='z' && c[len] >= 'a') continue;
}

int main() {
    read(a,len_a);
    //fflush(stdin);
    read(b,len_b);
    make_nxt();
    censor();
    //cout << tot <<endl;
    for(int i = 1 ; i <=tot ; ++i) putchar(a[loc[i]]);
    puts("");
    isdigit(1);
    return 0;
}