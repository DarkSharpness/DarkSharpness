#include "1040.hpp"
#include <Dark/inout>
#include <array>
#include <algorithm>
int cmp(int a,int b) {return a > b;}


signed main() {
    int a[19] = {1,7,5,4,10,6,2,3,8,9};
    dark::writeRange(a,a + 10);
    putchar('\n');
    nth_element(a,a + 9,a + 10,cmp);
    dark::writeRange(a,a+10);
    return 0;
}