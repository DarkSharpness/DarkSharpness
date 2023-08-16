#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 10;
struct node { int cnt,val; } t[N];

bool cmp_1(node a, node b) {
    return a.val < b.val;
}
bool cmp_2(node a, node b) {
    if(a.cnt != b.cnt)
        return a.cnt < b.cnt;
    else
        return a.val < b.val;
}

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



int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) 
        t[i].val = read <int> ();
    std::sort(t, t + n, cmp_1);

    int j = 0;
    for(int i = 0 ; i < n ; ++i) {
        if(t[j].val == t[i].val) {
            t[j].cnt++;
        } else {
            ++j;
            t[j].cnt = 1;
            t[j].val = t[i].val;
        }
    }
    ++j;
    std::sort(t, t + j, cmp_2);
    int cnt = -1;
    for(int i = 0 ; i < j ; ++i) {
        if(cnt != t[i].cnt) {
            if(i) putchar('\n');
            cnt = t[i].cnt;
            write(t[i].cnt);
            putchar(' ');
            putchar(':');
            putchar(' ');
        }
        write(t[i].val);
        putchar(' ');
    }
    return 0;
}
