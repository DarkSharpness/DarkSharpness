#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 8;
bitset <N> b;
int vis[N];//mininal cost


#define endl '\n'
inline void getbit(int n) {
    static char ch;
    ll ans = 0;
    while(!isdigit(ch = getchar()));
    for(int i = 1 ; i <= n ; ++i) { 
        b[i] = bool(ch == '0');
        ch = getchar();
    }
    //b.flip();
    for(int i = 1 ; i <= n ; ++i) {
        if(b[i]) {
            int j = i;
            while(j <= n && b[j]) {
                if(!vis[j]) vis[j] = i;   
                j += i;
            }
            ans += vis[i];
        }
        vis[i] = 0; //Çå¿ÕvisÊý×é
    }
    printf("%lld\n",ans);
}



int main() {
    int T,n;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        getbit(n);
    }
    return 0;
}