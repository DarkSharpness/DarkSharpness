#ifndef _DARK_HASH_MAP_H_
#define _DARK_HASH_MAP_H_

#include "hash.h"
#include "allocator.h"

#include <iostream>
#include <string>

namespace dark {


/**
 * @brief Map for homework only. Do not use it!
 * 
 */
template <
    class key_t,
    class   T,
    size_t kTABLESIZE,
    class Hash    = std::hash <key_t>,
    class Compare = std::equal_to <key_t>
> 
class hash_map {
  public:
    using value_t = std::pair <const key_t,T>;
    struct iterator;

  private:

    using node_base = hash::node_base;
    using list_node = list::node_base;
    using baseptr   = hash::baseptr;
    using listptr   = list::baseptr;
    using node      = hash::node <value_t>;
    using pointer   = hash::node <value_t> *;
    using Implement = implement <node,std::allocator <node>,Compare,Hash>;

  private:

    Implement impl;     /* Implement of the map. */ 
    list_node header;   /* Header of list. */
    node_base cache;    /* Custom memory pool. */
    node_base table[kTABLESIZE]; /* Hash table. */

  private:
    
    bool find() {

    }



};


}

#endif
