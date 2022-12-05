#include "Dark/maths"
#include "Dark/inout"
// #include "Dark/string"
// #include <span>
// #include <vector>
// #include <string>
using namespace dark;

signed main() {
    complex <float> c;
    while(true) {
        read(c.real,c.imag);
        write(c.argument());
        endl();
    }
    return 0;
}