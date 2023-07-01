#include <iostream>
using namespace std;
using ll = long long;

__int128 &read(__int128 &num) {
    char ch;
    num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    } return num;
}

void writeline(__int128 num) {
    if(!num) return (void) puts("0");
    if(num < 0) num = -num,putchar('-');
    char ch[40] = {0};
    int top = 40;
    while(num) {
        ch[--top] = '0' ^ (num % 10);
        num /= 10;
    }
    puts(ch + top);
}

/* 请不要抄袭! */
signed main() {
    __int128 x,y;
    read(x); read(y);
    writeline(x + y);
    writeline(x - y);
    writeline(x * y);
    return 0;
}
