#include "src.hpp"
#include "utility.h"

template <int arrSize>
void test_func() {
    array <int, arrSize> a; // An array ? right ?
    static_assert(arrSize > 0 && sizeof(a) <= sizeof(char) * arrSize); // Impossible to store! We don't allow using ::new either!!!! HAHAAAAAAAAAA!
    for (int i = 1 ; i <= arrSize ; ++i) a[i] = dark::rand(); // Anti-hack!
    for (int i = arrSize ; i >= 1 ; --i) std::cout << a[i] << '\n'; // Anti-hack!
}

template <int arrSize>
void test_all() {
    if constexpr (arrSize > 0) {
        test_func <arrSize> (); std::cout << '\n';
        test_all  <arrSize - 1>();
    }
}

signed main() {
    test_all <10> ();
    return 0;
}
