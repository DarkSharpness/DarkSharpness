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

class hash_map {
  public:
    using value_t = std::pair <key_t,T>;

  private:

    struct iterator;

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
    node_base table[kTABLESIZE] = {};


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
    baseptr erase_back(const value_t &__v) {
        const key_t &__k = pointer(header.next)->data.first;
        baseptr __p = find_index(__k);
        --impl.count;
        while(__p->real) {
            if(Compare(impl)(__k,pointer(__p->real)->data.first)) {
                list::delink(static_cast <pointer> (__p->real));
                baseptr __tmp = __p->real;
                __p->real = __tmp->real;
                static_cast <pointer> (__tmp)->data = __v;
                __tmp->real = nullptr;
                return __tmp;
            }
        }
        throw 114514; /* This case won't happen. */
    }

    /* Insert after given node in the hash map. */
    void insert_after(const value_t &__v,baseptr __p) {
        if(__p->real) return;
        baseptr __n = impl.count++ == kMAPSIZE ?
                      erase_back(__v) : impl.alloc(hash::forward_tag(),__v);
        __p->real = __n;
        list::link_before(&header,static_cast <pointer> (__n));
    }

  public:

    hash_map() noexcept { header.next = header.prev = &header; }

    void insert(const value_t &__v)    { return insert_after(__v,find_pre(__v.first)); }

    void insert(const value_t &__v,iterator iter) { return insert_after(__v,iter.__p); }

    iterator try_find(const key_t &__k) { return {find_pre(__k)}; }

    void print() const noexcept {
        listptr __p = header.next;
        while(__p != &header) {
            listptr __n = __p->next; /* Next node. */
            std::cout << static_cast <pointer> (__p)->data.first << ' ';
            __p = __n;
        }
        std::cout << '\n';
    }

    ~hash_map() {
        listptr __p = header.next;
        while(__p != &header) {
            listptr __n = __p->next; /* Next node. */
            impl.dealloc(static_cast <pointer> (__p));
            __p = __n;
        }
    }

 private:

    /* Simple iterator implement. */
    struct iterator {
        baseptr __p; /* Pointer to node_base before the real data. */
        value_t *base() const noexcept
        { return __p->real ? &static_cast <pointer> (__p->real)->data : nullptr; }
    };

};

}

#endif
