#ifndef _DARK_ROUND_ARRAY_H_
#define _DARK_ROUND_ARRAY_H_

#include "../include/basic.h"
#include "../dynamic_array"

namespace dark {

using value_t = int;

class round_array : public dynamic_array <value_t> {
  protected:
    size_t offset; /* Offset of the array. Ranged in [0,size()) */

  public:
    round_array()
        : dynamic_array(),offset(0) {}
    round_array(const round_array &rhs)
        : dynamic_array(rhs),offset(rhs.offset) {}
    round_array(const round_array &rhs)
        : dynamic_array(rhs),offset(rhs.offset) {}
    

    value_t &operator [] (size_t __n) {
        __n = (__n + size() - offset) % size();
        return dynamic_array <value_t>::operator[](__n); 
    }
    const value_t &operator [] (size_t __n) const {
        __n = (__n + size() - offset) % size();
        return dynamic_array <value_t>::operator[](__n); 
    }
    

};


}

#endif
