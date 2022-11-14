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



}

#endif