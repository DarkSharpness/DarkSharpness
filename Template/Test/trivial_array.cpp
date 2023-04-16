#include <Dark/inout>
#include <Dark/memleak>
#include <Dark/trivial_array>
using namespace std;


signed main() {
    dark::trivial_array <int> t;
    t.push_back(1);
    t.copy_back(2);
    t.push_back(3);
    while(t.size()) dark::writeline(t.pop_back());
    return 0;
}