#include <iostream>
#include <algorithm>
#include <cstring>

/* 读入一个正整数. */
template <class integer>
integer read() {
    char ch;
    bool flag = false;
    integer num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) num = -num;
    return num;
}

/* 写一个正整数(无空格/换行) */
template <class integer>
void write(integer num) {
    if(!num) return (void) putchar('0');
    static char ch[24];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}

const int N = 36;
const int M = 1e5 + 3;
int len[N],tag[N];
int a[N][M];

signed main() {
    int n = read <int> ();
    int m = read <int> ();
    for(int i = 1 ; i <= n ; ++i) {
        len[i] = read <int> ();
        for(int j = 0 ; j < len[i] ; ++j)
            a[i][j] = read <int> ();
    }
    char buf[8];
    while(m--) {
        scanf("%s",buf);
        if(buf[0] == 'a') {
            int x = read <int> ();
            int y = read <int> ();
            // 复制 y 到 x 的尾部
            memcpy(a[x] + len[x],a[y],sizeof(int) * len[y]);
            len[x] += len[y];
            tag[x] = 1;
        } else {
            int x = read <int> ();
            if(tag[x]) {
                std::sort(a[x],a[x] + len[x]);
                tag[x] = 0;
            }
            for(int i = 0 ; i < len[x] ; ++i)
                write(a[x][i]) , putchar(' ');
            putchar('\n');
        }
    }
    return 0;
}
