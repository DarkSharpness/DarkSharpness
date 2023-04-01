#include<bits/stdc++.h>
//using namespace std;
using ull = size_t;
const int N = 4e5 + 3;
int n,m,maxn,len;
const ull mod = 998244353ULL;
int rev[N << 1];
const ull g[2] = { 3 , (mod+1) / 3 }; //g[0]原根 g[1]原根的逆元 

ull read_char() {
    char ch;
    while(!isdigit(ch = getchar()));
    return ch - '0';
}

inline ull fast_pow(ull base,ull pow) {
    ull res = 1;
    while(pow) {
        if(pow&1) res = (res*base)%mod;
        base = (base * base) %mod;
        pow >>= 1;
    }
    return res;
}

void FFT(ull* A ,int length,int flag = 0){
    for(int i = 0 ; i < length; ++i){
        if(i < rev[i]) std::swap(A[i],A[rev[i]]);
        // A[i] %= mod;
    }
    for(int i = 1; i < length; i<<=1) {
        ull wn = fast_pow(g[flag],(mod-1)/(i<<1));
        for(int j = 0; j < length; j+=(i<<1)) {
            ull temp = 1;
            for(int k = 0; k < i; ++k) {
                ull x = A[j+k] , y =A[j+k+i]*temp % mod;
                A[j+k]   = (x + y) % mod;
                A[j+k+i] = (x - y + mod) % mod;
                temp = (temp*wn) % mod;
            }
        }
    }
}

void IFFT(ull* A,int length) { FFT(A,length,1); }

ull a[N << 1],b[N << 1];



/* Write a integer. */
template <class integer>
void writeInt(integer num) {
    if(!num) return (void) putchar('0');
    if(num < 0) num = -num , putchar('-');
    static char ch[3 * sizeof(integer)];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i = 0 ; i <= n ; ++i) a[i] = read_char();
    for(int i = 0 ; i <= m ; ++i) b[i] = read_char();
    maxn = 1;
    len  = 0;
    while(maxn <= n+m) maxn <<= 1 , len++;
    for(int i = 0 ; i < maxn ; i++)
        rev[i]= ( rev[i>>1]>>1 )| ( (i&1) * maxn >> 1 ) ;// 1 << len+1 = maxn
    FFT(a,maxn);
    FFT(b,maxn);
    for(int i = 0 ; i <=maxn ; ++i) a[i] *= b[i];   
    IFFT(a,maxn);
    ull inv = fast_pow(maxn,mod-2);
    for(int i = 0 ; i <= n+m ; ++i) {
        writeInt(a[i] * inv % mod);
        putchar(' ');
    }
    return 0;
}
