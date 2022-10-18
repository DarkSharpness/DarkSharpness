#include <General/inout.h>
#include <General/basic.h>

using namespace dark;
class test {
    public:
        friend const out_stream& operator <<(out_stream &os,const test &t){
           puts("Hello!");
           return os;
        }
    test() {
        
    }
};

int main() {
    int c;
    while(din >> c) {
        dout << (long long)(c) * c << endd;
    }
    
    return 0;
}