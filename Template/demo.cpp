#include "Dark/inout"
#include "Dark/algos"
// #include "Dark/string"
// #include <span>
// #include <vector>
// #include <string>
using namespace dark;

constexpr int N = Max(1,2,4,3,0);
constexpr int M = Min(61,-1,3,-3);
constexpr int a[N] = {1,5,-7,9};
constexpr int MAX = MaxIn(a,a + 4);
signed main() {
    int b[N];

    readRange(b);
    writeRange(b);endl();
    write(MaxIn(b,b + 3));
    return 0;
}