#include "buddy.h"
#include "impl.h"

signed main() {
    dark::alloc.first_init();

    void *p1 = dark::malloc(1);
    void *p2 = dark::malloc(31);

    dark::free(p1, 64);

    dark::debug();
    return 0;
}
