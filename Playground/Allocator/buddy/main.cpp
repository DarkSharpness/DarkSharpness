#include "buddy.h"
#include "impl.h"

signed main() {
    dark::free(dark::malloc(1), 1);
    dark::debug();
    return 0;
}
