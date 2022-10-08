#include <General/inout.h>
#include <algorithm>
using namespace dark;

int main() {
    int n;
    read_u(n);
    Loop(i,0,n) 
        write("# # \n",i,i*i);
}