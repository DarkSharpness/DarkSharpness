#ifndef _BINARY_INDEX_ARRAY_
#define _BINARY_INDEX_ARRAY_
#include <vector>
#include <Math/binfunc.h>

namespace std{
typedef int value;
/**
 * @brief A binary index array ranging [0,siz)
 * It can calculate the sum in a range,
 * Add a sum to the 
 * 
 * @tparam value The value you want to know. 
 * @tparam siz   The maximum of the range.
 */
template <
    size_t siz>
class binarray
{
    value v[siz];
public:
    inline void add(const value &_X,size_t _loc)
    {
        for(   ;_loc<siz;_loc+=lowbit(_loc)) v[_loc]+=_X;
    }
    binarray(const value _D[]&)
    {
        copy(_D,_D+siz,v);
    }
    binarray(const value _D[]&,const size_t _len)
    {
        copy(_D,_D+_len,v);
    }
};





}

#endif