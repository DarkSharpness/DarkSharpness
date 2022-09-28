#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 4e7 + 4;
int n, k;
int st[3][N];//顶部

template <class T>
inline void Fread(T &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
} 

inline void read() {
}

template <class T,class ...V>
void read(T &arg,V &...args) {
    Fread(arg);
    read(args...);
}

void read_input_data() {
    int m;
    read(n,k,m);
    for (int i = 1; i <= m; i++) read(st[0][i]);
    unsigned int z = st[0][m];
    for (int i = m + 1; i <= n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        st[0][i] = z & 0x7fffffff;
    }
}


inline int rand_in(int _size) {
    return 1+(rand() % _size);
}

char ch[12];
int tot = 0;
inline void Fwrite(int &tmp) {
    while(tmp) {
        ch[++tot] = (tmp%10) ^ '0';
        tmp /= 10;
    }
    while(tot) putchar(ch[tot--]);
}


int main() {
    read_input_data();
    int now;  
    int *cur = st[0],
        *pre = st[1],
        *suc = st[2],
         ran        ;
    int  top_pre,
         top_suc;
    srand(1919810 % 114514);//wtf!
    while(1) {
        //st[pre] 比 now 小
        //st[suc] 不小于 now
        ran = rand_in(n);
        now = cur[ran];
        top_pre = top_suc = 0;
        for(int i = 1 ; i < ran ; ++i) {
            if(cur[i] < now) pre[++top_pre] = cur[i];
            else suc[++top_suc] = cur[i];
        }
        for(int i = ran+1 ; i <= n ; ++i) {
            if(cur[i] < now) pre[++top_pre] = cur[i];
            else suc[++top_suc] = cur[i];
        }
        
        if(top_pre == k-1) {
            Fwrite(now);
            break;
        } 
        if(top_pre < k -1) {
            n = top_suc;
            k -= (top_pre + 1);
            swap(cur,suc);
        } else {
            n = top_pre;
            swap(cur,pre);
        }
    }
    return 0;
}