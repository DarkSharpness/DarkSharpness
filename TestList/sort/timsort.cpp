#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;
using ll = long long;
using ull = unsigned long long;
// #define int long long

using RandomIt = int *;
using Compare  = std::less<int>;

int a[16];

/* Guarantee that begin < end. */
void scansort(RandomIt begin,RandomIt end,Compare comp) {
    RandomIt front = begin;
    bool flag      = false;
    while(++begin != end) {
        if(flag == comp(*begin,*(begin - 1))) continue;
        if(flag) { // last <= begin
            std::reverse(front,begin);
            flag = false;
        } else {    // last > begin
            front = begin;
            flag  = true;
        }
    }
    if(flag) std::reverse(front,begin);
}

void timsort(RandomIt begin,RandomIt end,Compare comp) {
    if(end - begin  <= 32) return ; // Brute force
    scansort(begin,end,comp);
    

}


signed main() {
    dark::readRange(a);
    dark::writeRange(a,a+16);
    putchar('\n');
    scansort(a,a + 16,less<int>());
    dark::writeRange(a,a+16);
    putchar('\n');

    return 0;
}