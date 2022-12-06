#ifndef _HEADER_HPP_
#define _HEADER_HPP_
#include <cstddef>

namespace dark {

template <class value_t>
inline void swap(value_t &X,value_t &Y) {
    // X ^= Y;Y ^= X;X ^= Y;
    value_t tmp = std::move(X);
    X = Y; Y = tmp;
}


}



#endif

