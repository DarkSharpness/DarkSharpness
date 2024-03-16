#include <locale>
#include <stdio.h>
#include <tuple>

template <class T>
void read_signed(T &__n) {
    char __c; /* Char. */
    bool __f; /* Flag. */
    __n = 0;
    while(!isdigit(__c = getchar()))
        if(__c == '-') __f = true;
    while(isdigit(__c)) {
        __n = __n * 10 + (__c ^ '0');
        __c = getchar();
    }
    /* If T is not trivial, use std::move to save space. */
    if(__f) __n = -__n;
}


template <class T>
void read_unsigned(T &__n) {
    char __c;
    while(!isdigit(__c = getchar()));
    while(isdigit(__c)) {
        __n = __n * 10 + (__c ^ '0');
        __c = getchar();
    }
}

template <class T>
T read_one() {
    T __tmp;
    read_signed(__tmp);
    return __tmp;
}

template <class T,class ...V>
std::tuple <T,V...> read() {
    return
        std::make_tuple(
            read_one <T> (),
            read_one <V> ()...
        );
}


/* Write a integer and start a new line.*/
template <class T>
void writeline_integer(T __n) {
    if(!__n) return (void) puts("0");
    if(__n < 0) __n = -__n,putchar('-');
    static char ch[3 * sizeof(T) + 1] = {0};
    int top = 3 * sizeof(T) - 1;
    while(__n) {
        ch[--top] = '0' ^ (__n % 10);
        __n /= 10;
    }
    puts(ch + top);
}



signed main() {
    auto [x,y,z] = read <int,int,int> ();
    writeline_integer(x);
    std::tuple <int,int,int> h;
    std::
    writeline_integer(y);
    writeline_integer(z);
    return 0;
}