#include <Dark/memleak>
#include "LRUmap.h"
using namespace std;

int a[] = {
    1,2,3,4,5,4,1
};

signed main() {
    dark::LRU_map <int,int> m;
    for(auto iter : a) {
        auto tmp = m.try_find(iter);
        if(!tmp.base()) m.insert(iter,0,tmp);
        std::cout << m.full() << ':';
        m.print();
    }
    return 0;
}