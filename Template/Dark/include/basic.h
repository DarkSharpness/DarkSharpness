#ifndef _DARK_BASIC_H_
#define _DARK_BASIC_H_
#include <string.h>
#include <stdint.h>
#include <ctype.h>

// DarkSharpness's namespace.
namespace dark {



#define Iter(it,begin,end) for(auto it = begin ; it != end ; ++it)
#define Loop(it,begin,end) for(auto it = begin ; it <= end ; ++it)
#define Riter(it,begin,end) for(auto it = begin ; it != end ; --it)
#define Rloop(it,begin,end) for(auto it = begin ; it >= end ; --it)

/**
 * @brief Fast built-in LOG2 function from
 * "骆可强《论程序底层优化的一些方法与技巧"
 * You can access that at 
 * https://github.com/lzyrapx/Competitive-Programming-Docs/.
 * 
 * 
 * @return log2(x) in 32-bit.
 */
inline unsigned int LOG2(unsigned x){
    unsigned ret;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}


}

#endif