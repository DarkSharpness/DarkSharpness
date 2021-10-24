#ifndef _BINARY_FUNCTION_H_
#define _BINARY_FUNCTION_H_

namespace std{



/**
 * @brief Find the lowest bit value in O(1)
 * 
 * @tparam Value Only support (unsigned) int or long long or such.
 * @param _X The value to find lowbit with.
 * @return The lowest bit value.(Not the bit place.)
 */
template <typename value>
inline value lowbit(const value &_X)
{
    return _X&(-_X);
}



/**
 * @brief A fast Log2 function for basic number type.
 * 
 * @tparam Value Only support (unsigned) int or long long or such.
 * @param x The base value.
 * @return The lowest bit location number.(Log2(x))
 */
template <typename value>
inline unsigned int Log2(const value &_X){
    unsigned int ret;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(_X));
    return ret;
}




}


#endif