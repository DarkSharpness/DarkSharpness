#include <iostream>
using namespace std;

signed main() {
    while(true) {
        char ch = getchar();
        if(ch == '0') break;
        if(ch == '_') putchar('0');
        else putchar(ch);
    }
    return 0;
}
