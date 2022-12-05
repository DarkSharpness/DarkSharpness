#ifndef _COMPARE_HPP_
#define _COMPARE_HPP_

#include "../include/basic.hpp"


namespace dark {



/* Return the Maximum value. */
template <class value_t>
constexpr const value_t &Max(const value_t & arg) {
    return arg;
}
/* Return the Maximum value. */
template <class value_t>
constexpr const value_t &Max(const value_t &X,const value_t & Y) {
    return Y < X ? X : Y;
}
/* Return the Maximum value. */
template <class value_t,class ...value_s>
constexpr const value_t &Max(const value_t & arg,const value_s & ...args) {
    return Max(arg,Max(args...));
}
/* Return the Maximum value in a range. 
   Ensure that begin < end */
template <class Iterator>
constexpr const auto &MaxIn(Iterator begin,Iterator end) {
    Iterator iter = begin;
    while(++begin != end) {
        if(*iter < *begin) iter = begin;
    }
    return *iter;
}
/* Return the Maximum value in a range. 
   Ensure that begin + len <= end */
template <class Iterator>
constexpr const auto &MaxIn(Iterator begin,size_t len) {
    Iterator iter = begin;
    while(--len) {
        ++begin;
        if(*iter < *begin) iter = begin;
    }
    return *iter;
}




/* Return the Minimum value. */
template <class value_t>
constexpr const value_t &Min(const value_t & arg) {
    return arg;
}
/* Return the Minimum value. */
template <class value_t>
constexpr const value_t &Min(const value_t &X,const value_t & Y) {
    return X < Y ? X : Y;
}
/* Return the Minimum value. */
template <class value_t,class ...value_s>
constexpr const value_t &Min(const value_t & arg,const value_s & ...args) {
    return Min(arg,Min(args...));
}
/* Return the Minimum value in a range. 
   Ensure that begin < end */
template <class Iterator>
constexpr const auto &MinIn(Iterator begin,Iterator end) {
    Iterator iter = begin;
    while(++begin != end) {
        if(*begin < *iter) iter = begin;
    }
    return *iter;
}
/* Return the Maximum value in a range. 
   Ensure that begin + len <= end */
template <class Iterator>
constexpr const auto &MinIn(Iterator begin,size_t len) {
    Iterator iter = begin;
    while(--len) {
        ++begin;
        if(*begin < *iter) iter = begin;
    }
    return *iter;
}


}



#endif
