#include<new>
#include<bits/move.h>
#include<string.h>
#include<inttypes.h>

#ifndef _DARK_BASIC_H_
#define _DARK_BASIC_H_

namespace dark{

#define Iter(it,begin,end) for(auto it = begin; it != end ; ++it)
#define Loop(it,begin,end) for(auto it = begin; it <= end ; ++it)
#define until(condition) while(!(condition))
#define unless(condition) if(!(condition))
#define RIter(it,begin,end) for(auto it = begin ; it != end ; --it)
#define RLoop(it,begin,end) for(auto it = begin ; it >= end ; --it)
using size_type = unsigned int;


namespace private_space { // Don't use this namespace unless neccesary!

}




}
#endif