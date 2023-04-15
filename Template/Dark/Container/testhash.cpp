#include <Dark/memleak>
#include "LRUmap.h"
using namespace std;

int a[] = {
    1,2,3,4,5,4,1
};

signed main() {
    dark::hash_map m;
    for(auto iter : a) {
        m.insert({iter,""});
        m.print();
    }
    return 0;
}