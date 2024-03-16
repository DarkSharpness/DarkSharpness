#include <Dark/inout>
#include <Dark/memleak>
#include <Dark/trivial_array>


signed main() {
    dark::trivial_array <long long> t;
    t.push_back(1);
    t.copy_back(2);
    t.push_back(3);
    dark::trivial_array <std::pair <int,int>> v = {{0,0},{3,0}};
    swap(t,v);
    while(t.size()) dark::writeline(t.pop_back());
    return 0;
}
