#ifndef _DARK_LRU_H_
#define _DARK_LRU_H_

#include "hash.h"
#include "allocator.h"

#include <iostream>
#include <string>

namespace dark {

using key_t   = long;
using   T     = std::string;
using Hash    = std::hash <key_t>; 
using Compare = std::equal_to <key_t>;

constexpr size_t kTABLESIZE = 1019;
constexpr size_t kMAPSIZE   = 5;

template <
    class key_t,
    class   T,
    class Hash = std::hash <key_t>,
    class Compare = std::equal_to <key_t>
> 
class LRU_map {
  public:
    using value_t = std::pair <key_t,T>;
    struct iterator;

  private:


    using node_base = hash::node_base;
    using list_node = list::node_base;
    using baseptr   = hash::baseptr;
    using listptr   = list::baseptr;
    using node      = hash::node <value_t>;
    using pointer   = hash::node <value_t> *;
    using implement = implement <node,std::allocator <node>,Compare,Hash>;

  private:

    implement impl;
    list_node header;
    node_base table[kTABLESIZE];


  private:

    /* Access a node and update it. */
    void access(baseptr __p) {
        list::delink(static_cast <pointer> (__p));
        list::link_before(&header,static_cast <pointer> (__p));
    }

    /* Return the index of the real node. */
    baseptr find_index(const key_t &__k) noexcept
    { return &table[Hash(impl)(__k) % kTABLESIZE]; }

    /* Find the previous node in hash-map and access it.  */
    baseptr find_pre(const key_t &__k) {
        baseptr __p = find_index(__k);
        while(__p->real) {
            if(Compare(impl) (__k,static_cast <pointer> (__p->real) -> data.first)) 
            { access(__p->real); return __p; }
            __p = __p->real;
        }
        return __p;
    }

    /* Erase the oldest pair and modify it to the new one. */
    baseptr erase_back(const key_t &__k,const T &__t) {
        const key_t &__n = pointer(header.next)->data.first;
        baseptr __p = find_index(__n);
        --impl.count;
        while(__p->real) {
            if(Compare(impl)(__n,pointer(__p->real)->data.first)) {
                list::delink(static_cast <pointer> (__p->real));
                baseptr __tmp = __p->real;
                __p->real = __tmp->real;
                static_cast <pointer> (__tmp)->data.first  = __k;
                static_cast <pointer> (__tmp)->data.second = __t;
                __tmp->real = nullptr;
                return __tmp;
            }
        }
        throw 114514; /* This case won't happen. */
    }

    /* Insert after given node in the hash map. */
    void insert_after(const key_t &__k,const T &__t,baseptr __p) {
        if(__p->real) return;
        baseptr __n = full() ? erase_back(__k,__t) : 
                               impl.alloc(hash::forward_tag(),__k,__t);
        ++impl.count;
        __p->real = __n;
        list::link_before(&header,static_cast <pointer> (__n));
    }

  public:

    LRU_map() noexcept : header({&header,&header}) {}

    ~LRU_map() {
        listptr __p = header.next;
        while(__p != &header) {
            listptr __n = __p->next; /* Next node. */
            impl.dealloc(static_cast <pointer> (__p));
            __p = __n;
        }
    }

    /* Insert after given iterator. */
    void insert(const key_t &__k,const T &__t,iterator iter)
    { return insert_after(__k,__t,iter.__p); }

    /* Try to find an element. */
    iterator try_find(const key_t &__k) { return {find_pre(__k)}; }

    /* Return reference to last node. */
    value_t *last() { return & static_cast <pointer> (header.next) ->data; }

    /* Judge whether the map is full. */
    bool full() const noexcept { return impl.count == kMAPSIZE; }

    /* Return count of elements in the map. */
    size_t size() const noexcept { return impl.count; }

    /* DEBUG USE ONLY! */
    void insert(const key_t &__k,const T &__t)
    { return insert_after(__k,__t,find_pre(__k)); }

    /* DEBUG USE ONLY! */
    void print() const noexcept {
        listptr __p = header.next;
        while(__p != &header) {
            listptr __n = __p->next; /* Next node. */
            std::cout << static_cast <pointer> (__p)->data.first << ' ';
            __p = __n;
        }
        std::cout << '\n';
    }

 public:

    /* Simple iterator implement. */
    struct iterator {
        baseptr __p; /* Pointer to node_base before the real data. */
        value_t *base() const noexcept
        { return __p->real ? &static_cast <pointer> (__p->real)->data : nullptr; }
    };

};

}

#endif
