#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int k,q;
ll l,r;
const int N = 1e5 + 10;
char c[N];
char s[N];
int lenc,lens;
int loc1,loc2;
int n,q;


int main() {
    scanf("%s%s",c+1,s+1);
    lenc = strlen(c+1);
    lens = strlen(s+1);
    for(int i = 1 ; i <= lens ; ++i) {
        if(c[lens] == '$') {
            if(!loc1) loc1 = i;
            else loc2 = i;
        }
    }
    scanf("%d%d",&n,&q);
    if(loc2 == 0) {
        
    }   

    return 0;
}