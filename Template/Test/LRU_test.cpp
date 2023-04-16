#include <Dark/memleak>
#include <Dark/LRU_map>
using namespace std;

int a[] = {
    1,2,3,4,5,4,1,7
};

signed main() {
    dark::LRU_map <int,int> m;
    for(auto iter : a) {
        auto tmp = m.try_find(iter);
        if(!tmp.next_data()) m.insert(iter,0,tmp,m.size() == 5);
        // m.print();
        for(auto &&iter : m) std::cout << iter.first << ' ';
        std::cout << '\n';
    }
    m.erase(1);
    m.print();
    m.insert(3,2);
    m.print();
    return 0;
}