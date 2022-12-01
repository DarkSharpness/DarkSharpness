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




// class string : private std::allocator <char> {
//   private:
//     char *head; /* To first char */
//     char *tail; /* To last char '\0' */
//     char *term; /* To last capable char */
//     inline void expand(size_t __N) {
//         char *temp = allocate(__N + 1);
//         memcpy(temp,head,size());
//         tail += (temp - head);
//         this->~string();
//         term = (head = temp) + __N;
//         memset(tail,0,remainder() + 1);
//     }
//   public:
//     /* Remove all allocated space. */
//     ~string() {deallocate(head,capacity() + 1);}
//     /* Initialize with nullptr.*/
//     string() {head = tail = term = nullptr;}
//     string(size_t length) {expand(length);}
//     /* Move a string. */
//     string(string &&str) {swap(str);}
//     /* Copy a char * style string. */
//     string(const char *ptr) {
//         tail = head = const_cast <char *> (ptr);
//         while(*tail) ++tail;
//         head = allocate(tail - head + 1);
//         term = tail += (tail - head);
//         memcpy(head,ptr,capacity());
//         *term = '\0';
//     }
//     /* Copy a string*/
//     string(const string &str) {
//         head = allocate(str.size() + 1);
//         term = tail = head + str.size();
//         memcpy(head,str.head,size());
//         *tail = '\0';
//     }
//     inline size_t size()      const{return tail - head;}
//     inline size_t capacity()  const{return term - head;}
//     inline size_t remainder() const{return term - tail;}

//     string &copy(const string &str) {
//         if(this == &str) return *this;
//         if(size() < str.size()) {
//             this->~string();
//             head = allocate(str.size() + 1);
//             term = tail = head + str.size();
//             memcpy(head,str.head,size());
//         } else {
//             memset(head + str.size(),0,size() - str.size());
//             memcpy(head,str.head,str.size());
//         }
//         return *this;
//     }
//     string &swap(string &str) {
//         std::swap(str.head,head);
//         std::swap(str.tail,tail);
//         std::swap(str.term,term);
//         return *this;
//     }
//     friend inline void swap(string &X,string &Y) {X.swap(Y);}
//     inline char &operator [](size_t index)      {return head[index];}
//     inline char operator [](size_t index) const {return head[index];}
//     const char *find(char _ch,size_t index = 0) const {
//         const char *ptr = head + index;
//         while(ptr != tail && *ptr != _ch) ++ptr;
//         return ptr;
//     }
//     string &operator +=(const string &str) {
//         if(remainder() < str.size()) {expand(str.size() + size());}
//         memcpy(tail,str.head,str.size());
//         return *this;
//     }
//     friend string operator +(const string &X,const string &Y) {
//         string X();

//     }


// };





}


#endif