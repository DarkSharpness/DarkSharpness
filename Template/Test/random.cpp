#include <Dark/random>
#include <Dark/inout>


signed main() {

    for(int i = 0 ; i < 20 ; ++i)
        dark::writeline(dark::random_in(1,10));

    return 0;
}
