#ifndef _DARK_LRU_H_
#define _DARK_LRU_H_

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

    /* Erase the oldest pair and modify it to the new one. */
    baseptr erase_back(const key_t &__k,const T &__t,baseptr &__i) {
        const key_t &__n = pointer(header.next)->data.first;
        baseptr __p = find_index(__n);
        --impl.count;
        while(__p->real) {
            if(Compare(impl)(__n,pointer(__p->real)->data.first)) {
                list::delink(static_cast <pointer> (__p->real));
                baseptr __tmp = __p->real;
                
                if(__i == __p->real) __i = __p;
                else  __p->real = __tmp->real;

                static_cast <pointer> (__tmp)->data.first  = __k;
                memcpy(&static_cast <pointer> (__tmp)->data.second,
                       &__t,
                       sizeof(T));
                __tmp->real = nullptr;
                return __tmp;
            }
        }
        throw 114514; /* This case won't happen. */
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

    /* Tries to insert key-value pair to hash_map. */
    void insert(const key_t &__k,const T &__t,bool flag = false)
    { return insert(__k,__t,find_pre(__k),flag); }

    /* Insert after given iterator. Flag to determine whether to erase_back. */
    iterator insert_after(const key_t &__k,const T &__t,iterator iter,bool flag = false) {
        baseptr __p = iter.__p;
        if(__p->real) return iter;
        baseptr __n = flag ? erase_back(__k,__t,__p) : 
                             impl.alloc(hash::forward_tag(),__k,__t);
        ++impl.count;
        __p->real = __n;
        list::link_before(&header,static_cast <pointer> (__n));
        return {__p};
    }

    /* Find the previous node in hash_map and access it.  */
    iterator find_pre(const key_t &__k) {
        baseptr __p = find_index(__k);
        while(__p->real) {
            if(Compare(impl) (__k,static_cast <pointer> (__p->real) -> data.first)) 
            { access(__p->real); break; }
            __p = __p->real;
        } return {__p};
    }

    /* Tries to erase certain element from hash_map. */
    void erase(const key_t &__k) { return erase(find_pre(__k)); }

    /* Erase element after given iterator in hash_map.  */
    void erase_after(iterator iter) {
        baseptr __p = iter.__p;
        if(!__p->real) return;
        --impl.count;
        baseptr __t = __p->real;
        __p->real   = __t->real;
        list::delink(static_cast <pointer> (__t));
        impl.dealloc(static_cast <pointer> (__t));
    }

    /* Return pointer to last node's value. */
    value_t *last() { return & static_cast <pointer> (header.next) ->data; }

    /* Return count of elements in the map. */
    size_t size() const noexcept { return impl.count; }

 public:

    /* Simple iterator implement. */
    struct iterator {
        baseptr __p; /* Pointer to node_base before the real data. */
        /* Return pointer to real data in next node in hash_map. */
        value_t *next_data() const noexcept
        { return __p->real ? &static_cast <pointer> (__p->real)->data : nullptr; }

        iterator &operator ++(void) noexcept { 
            __p = static_cast <pointer> (static_cast <pointer> (__p)->next);
            return *this;
        }

        value_t &operator * (void) const noexcept
        { return  static_cast <pointer> (__p)->data; }

        value_t *operator ->(void) const noexcept
        { return &static_cast <pointer> (__p)->data; }

        void *base() const noexcept { return __p; }
    };

    iterator begin() { return { static_cast <pointer> (header.next) }; }
    iterator end()   { return { static_cast <pointer> (&header) }; }

    friend bool operator != (const iterator &lhs,const iterator &rhs) 
    noexcept { return lhs.base() != rhs.base(); }

};


}

#endif
