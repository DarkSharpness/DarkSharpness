#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int N = 2e5 + 16;
constexpr int M = 3e5 + 16;
inline void read(int& tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^'0');
        ch = getchar();
    }
}

inline void print(int tmp) {
    static char ch[22];
    int tot = 0;
    while(tmp) {
        ch[++tot] = (tmp%10) ^ '0' ;
        tmp/=10;
    }
    while(tot) putchar(ch[tot--]);
    putchar(' ');
}

int a[N];
int n;
ll ans = 0;

struct FK{
    struct square {
        int cnt[M];
        int sqr[M]; // i所在块
        int tag[M]; // 第i块的标签
        int end[M]; // 第i块的结尾
        int sqrs;
        inline void insert(int loc) {
            for(int i = loc ; i <= end[sqr[loc]] ; ++i)
                ++cnt[i];
            for(int i = sqr[loc]+1 ; i <= sqrs ; ++i)
                ++tag[i];
        }
        inline int operator[](int loc) {
            return tag[sqr[loc]] + cnt[loc];
        }
        inline void init(int num) {
            int sqrn = sqrt(num);
            int i = 1,j = 1,k = 1;
            while(i <= num) {
                if(j > sqrn) {
                    j -= sqrn; 
                    end[k] = i-1;
                    ++k;
                }
                sqr[i] = k;
                ++i,++j;            
            }
            end[k] = num;
            sqrs   = k;
        }
    }s;




    inline int insert(int x) {
        
    }
    inline void init(int x) {
        s.init(x);
    }

}t;

void bf() {

}

int main() {
    read(n);
    int tmp = 0;
    for(int i = 1 ; i <= n ; ++i) {
        read(a[i]);
        tmp = max(tmp,a[i]);
    }
    if(n <= 3000) {
        bf();
        return 0;
    }
    t.init(tmp);
    for(int i = 1 ; i <= n ; ++i) {
        ans += t.insert(a[i]);
    }
    return 0;
}