#include<General/inout.h>
#include<Data/FW_tree.h>
using namespace dark;
typedef long long ll;
FW_tree <int,10> t;



int main() {
    int n = 1,x;
    while(n) {
        din >> n >> x ;
        t[n] = x;
        for(int i = 1 ; i <= 10 ; ++i) {
            dout << (long long)(t[i]) << ' ';
        }
        dout << dend;
    }


    return 0;
}