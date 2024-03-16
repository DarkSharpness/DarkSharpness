#include <bits/stdc++.h>
// #include <Dark/inout>

/* Judge whether a char is visible. */
inline bool is_char(char __c) { return __c > 32 && __c < 127; }

/* Read one visible char. */
char &read_char(char &__c) { while(!is_char(__c = getchar())); return __c; }

/* Whether brackets matches or not. */
inline bool match(char pre,char pos) { return pre < pos && pos < pre + 3; }

const int N = 1e6 + 2; /* Maximum stack size. */

struct node { int prev; char str; } t[N];
int len = 0;

void push() {
    char bra = read_char(bra);
    t[++len].str = bra;
    if(bra == '(' || bra == '[' || bra == '{') {
        t[len].prev = len;
    } else {
        int front = t[len - 1].prev;
        if(front && match(t[front].str,bra)) 
             t[len].prev = t[front - 1].prev;
        else t[len].prev = len;
    }
}

void pop()   { if(len) --len; }
void print() { if(len) putchar(t[len].str); putchar('\n'); }
void query() { puts(!t[len].prev ? "YES" : "NO"); }

signed main() {
    int n;
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; ++i) {
        char opt = read_char(opt);
        switch (opt) {
            case '1': push();  break;
            case '2': pop();   break;
            case '3': print(); break;
            case '4': query(); break;
        }
    }
    return 0;
}
