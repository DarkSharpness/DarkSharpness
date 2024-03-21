#include "buddy.h"
#include "impl.h"

signed main() {
    dark::alloc.first_init();
    void *p1 = dark::malloc(1);

    dark::debug();
    return 0;
}
