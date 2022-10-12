#include <iostream>
const int N = 100010;

char st[N];
int top = 0;
char ch;
int main() {
    ch = getchar();
    while((ch | 1) == 49) { 
        //std::cout << ch << std::endl;
        if(!top) {st[++top] = ch;}
        else if(ch == st[top]) {
            if(ch == 49) {
                --top;
            } else {
                if(top >= 2 && st[top-1] == 49) top -= 2;
                else st[top] = 49;
            }
        } else {
            st[++top] = ch;
        }
        ch = getchar();
    }
    if(!top) puts("NULL");
    else for(int i = 1; i <= top; ++i)
        putchar(st[i]);
    return 0 ;
}
