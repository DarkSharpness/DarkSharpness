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

  private:

    implement impl;
    node_base header; /* Parent as root node || son[0] as largest || son[1] as smallest. */

    /* Return the root node of the tree. */
    baseptr root() const noexcept { return header.parent; }



  public:



};






}


signed main() {
    dark::deque d;
    return 0;
}


#endif
