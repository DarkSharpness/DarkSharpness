#include<General/inout.h>
#include<Data/FW_tree.h>
using namespace dark;
typedef long long ll;
FW_tree <int,10> t;



int main() {
    int n = 1,x;
    while(n) {
        din >> n >> x ;
        t[n] += x;
        for(int i : t) {
            dout << i << ' ';
        }
        t.begin();
        dout << dend;
    }


    return 0;
}