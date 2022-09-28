#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 16;

char a[N];
char b[N];


int main() {
    scanf("%s",a);
    scanf("%s",b);
    int len_a = strlen(a),
        len_b = strlen(b);
    reverse(a,a+len_a);
    reverse(b,b+len_b);
    len_a = max(len_a,len_b);
    bool ret = false;
    for(int i = 0 ; i < len_a ; ++i) {
        a[i] = (a[i] ? a[i] ^ '0') + (b[i] ? b[i] ^ '0') + ret;
        if(a[i] >= 10) {
            a[i] -= 10;
            ret = true;
        } else {
            ret = false;
        }
    }
    if(ret) putchar('1');
    for(int i = len_a-1 ; i != -1 ; --i) 
        putchar(a[i] ^ '0');
    return 0;
}