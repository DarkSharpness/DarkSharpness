#include <iostream>

inline int get_value(char x) {
    if(!x)  return 0;
    else    return x - '0' + 1;
}

inline char get_char(int x) {
    if(!x)  return 0;
    else    return x + '0' - 1;
}

const int N = 729 * 729; /* pow(3,12) */
int cnt[N];

signed main() {
    int n;
    scanf("%d",&n);

    for(int i = 0 ; i < n ; ++i) {
        char buffer[16] = {};
        scanf("%s",buffer);
        int value = 0;
        for(int j = 0 ; j < 12 ; ++j)
            value = value * 3 + get_value(buffer[j]);
        ++cnt[value];
    }

    for(int i = 1 ; i < N ; ++i) {
        if(!cnt[i]) continue;
        char buffer[16] = {};
        int value = i;
        for(int k = 0 ; k < 12 ; ++k) {
            buffer[11 - k] = get_char(value % 3);
            value /= 3;
        }
        for(int j = 0 ; j < cnt[i] ; ++j)
            printf("%s ",buffer);
    }
    return 0;
}