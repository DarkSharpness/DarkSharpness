#ifndef _DARK_STRING_HPP_
#define _DARK_STRING_HPP_

#include <bits/allocator.h>
#include "../include/basic.hpp"

namespace dark {


class string_view {
  private:
    const char *head; /* pointer to the first char */
    const char *tail; /* pointer to '\0' */
  protected:  
    string_view() = default;
  public:
    ~string_view() = default;
    string_view(const char *ptr): head(ptr),tail(ptr) {while(*tail) ++tail;}
    string_view(const char *ptr,size_t length):
        head(ptr),tail(ptr + length) {} 
    string_view(const char *_head,const char *_tail):
        head(_head),tail(_tail) {}
    char operator[] (size_t index) {
        return head[index];
    }
    const char *begin() const{return head;}
    const char *end()   const{return tail;}
};






}


#endif