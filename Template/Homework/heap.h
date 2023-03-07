#ifndef _FK_U_
#define _FK_U_

#include <iostream>
#include "exceptions.hpp"

namespace dark {

// using value_t = int;
// using Compare = std::less <int>;
template <class value_t,class Compare = std::less <value_t> >
class heap {
  private:

    struct node;
    struct implement;
    using pointer = node *;

    struct node {
        pointer ls;
        pointer rs;
        size_t dist;
        value_t val;

        template <class ...Args>
        node(pointer _l,pointer _r,size_t _d,Args &&...objs)
            : ls(_l),rs(_r),dist(_d),
              val(std::forward <Args> (objs)...) {}
    };

    struct implement : std::allocator <node> , Compare {
        size_t count;   /* Count of all the elements. */

        implement() noexcept : count(0) {}

        template <class ...Args>
        pointer alloc(pointer __l,pointer __r,size_t __d,Args &&...objs) {
            ++count;
            pointer __p = this->allocate(1);
            this->construct(__p,__l,__r,__d,std::forward <Args> (objs)...);
            return __p;
        }

        void dealloc(pointer __p) {
            --count;
            this->destroy(__p);
            this->deallocate(__p,1);
        }

    };

    pointer   root; /* Root node of the tree. */
    implement impl; /* Implement of function. */

    /* Merge 2 nodes x and y. */
    pointer merge(pointer x,pointer y) {
        if(!x) return y;
        if(!y) return x;
        /* Now x and y are not empty. */

        if(impl(x->val,y->val)) std::swap(x,y); // Smaller as y
        x->rs = merge(x->rs,y);      // Merge shorter rs with y.

        if(!x->ls || x->ls->dist < x->rs->dist)
            std::swap(x->ls,x->rs);  // ls should be longer than rs

        x->dist = x->rs ? x->rs->dist + 1 : 1;
        return x;
    }

    /* Copy node info from target node. */
    pointer copy(pointer __p) {
        if(!__p) return nullptr;
        return impl.alloc(copy(__p->ls),copy(__p->rs),__p->dist,__p->val);
    }

    /* Remove target node with its sub-tree.(With destruction.) */
    void remove(pointer __p) noexcept {
        if(!__p) return;
        remove(__p->ls);
        remove(__p->rs);
        impl.dealloc(__p);
    }

  public:

    /* Emptized. */
    heap() noexcept : root(nullptr) , impl() {}
    /* Copy content. */
    heap(const heap &rhs) { root = copy(rhs.root); }

    /* Move content. */
    heap(heap &&rhs) noexcept : root(rhs.root),impl(rhs.impl) 
    { rhs.root = nullptr; rhs.impl.count = 0; }

    /* Now heap is re-initialized to empty. */
    ~heap() noexcept { clear(); }

    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            clear();
            root = copy(rhs.root);
        }
        return *this;
    }

    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            clear();
            std::swap(root,rhs.root);
            std::swap(impl,rhs.impl);
        }
        return *this;
    }

    /* Clean all the elements. */
    void clear() noexcept { remove(root); root = nullptr; }

    /* Return const reference to the smallest element. */
    const value_t &top() const {
        if(!root) throw sjtu::container_is_empty();
        return root->val;
    }

    /* Push one element to the heap. */
    template <class ...Args>
    void emplace(Args &&...objs) {
        pointer temp = impl.alloc(nullptr,nullptr,1,std::forward <Args> (objs)...);
        try { root = merge(root,temp); }
        catch(...) { impl.dealloc(temp)  ; throw; }
    }

    /* Push one element to the heap. */
    void push(value_t &&obj) {
        pointer temp = impl.alloc(nullptr,nullptr,1,std::move(obj));
        try { root = merge(root,temp); }
        catch(...) { impl.dealloc(temp) ; throw; }
    }

    /* Push one element to the heap. */
    void push(const value_t &obj) {
        pointer temp = impl.alloc(nullptr,nullptr,1,obj);
        try { root = merge(root,temp); }
        catch(...) { impl.dealloc(temp) ; throw; }
    }

    /* Pop out the top element. */
    void pop() {
        if(!root) throw sjtu::container_is_empty();
        pointer temp = root;
        root = merge(root->ls,root->rs);
        impl.dealloc(temp);
    }

    /* Merge 2 heaps. */
    void merge(heap &rhs) {
        if(this == &rhs) return;
        root = merge(root,rhs.root);
        impl.count += rhs.size();

        rhs.root = nullptr;
        rhs.impl.count = 0;
    }

    bool empty()  const noexcept { return !root; }
    size_t size() const noexcept { return impl.count; }

};


}


namespace sjtu {

template <class T,class Compare = std::less <T>>
using priority_queue = dark::heap <T,Compare>;

}

#endif