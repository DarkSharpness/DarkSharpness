#ifndef _DARK_DEQUE_H_
#define _DARK_DEQUE_H_

#include <memory>
#include "tree.h"

namespace dark {

using value_t = long long;

class deque {
  public:
    
    struct iterator;
    struct const_iterator;

  private:

    using node_base = tree::node_base;
    using baseptr   = tree::node_base *;
    using node      = tree::node <std::pair<size_t,value_t>>;
    using pointer   = tree::node <std::pair<size_t,value_t>> *;
    using implement = tree::implement <node>;

  public:
    struct iterator : tree::index_iterator <0,1> {
      protected:
        using Base    = tree::index_iterator <0,1>;
        using baseptr = typename iterator_base <0,1> ::baseptr;
      public:
        iterator(baseptr __p = nullptr,size_t __n = 0)
        noexcept : index_iterator(__p,__n) {}

        

    };

  private:

    implement impl;
    node_base header; /* Parent as root node || son[0] as largest || son[1] as smallest. */

    /* Return the root node of the tree. */
    baseptr root() const noexcept { return header.parent; }

     /* Special case : insert at root node. */
    iterator insert_root(baseptr __n) {
        ++impl.count;
        header.parent = header.son[0] = header.son[1] = __n;
        __n->parent   = &header;
        __n->color    = tree::Color::BLACK;
        return iterator(__n,0);
    }


  public:



};






}


signed main() {
    dark::deque d;
    return 0;
}


#endif
