#include <Dark/Container/iterator.h>
#include <Dark/inout>
#include <vector>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace dark::RandomAccess;

signed main() {
    iterator_base <int,0,0> iter(new int[2] {3,2});
    --iter;
    dark::writeline(*iter);
    iterator_base <int,1,0> temp = iter++;
    dark::writeline(*iter,*(iter - 1),iter - temp);
    if(iter != temp) puts("6");
    if(--iter == temp) puts("7");
    dark::writeline(iter[1]);

    std::vector <int> v = {1,2,3};
    dark::writeline((++v.rbegin())[1]);
    return 0;
}