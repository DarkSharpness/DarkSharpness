#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1024;
const int M = 3432; //14C7
int m,n,k;

short cnt[1<<14];
int loc[14];
int a[N];



//state
inline void work(short state) {
         

}



inline void count() {
    cnt[0] = 0 ;
    for(short i = 0 ; i < 1<<(m-1) ; ++i) {
        cnt[i<<1]   = cnt[i];
        cnt[i<<1|1] = cnt[i] + 1;
        if(cnt[i] == m>>1) work(i);
    }

}



int main() {
    scanf("%d%d",&n,&k);
    for(int i = 1 ; i <= n ; ++i) {
        scanf("%d",a+i);
        if(!a[i]) loc[m++] = i;
    }
    count();
    return 0;
}