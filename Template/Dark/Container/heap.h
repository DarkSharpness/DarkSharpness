#ifndef _DARK_HEAP_H_
#define _DARK_HEAP_H_


#include "allocator.h"


#include <cstddef>
#include <memory>


namespace dark {




template <class value_t>
class heap {
  private:

    struct node;
    using pointer = node *;

    dark::single_allocator <node> _Alloc; /* Allocator. */
    pointer root;    /* Root node of the tree. */

    /* Merge 2 nodes x and y. */
    static pointer merge(pointer x,pointer y) {
        if(!x) return y;
        if(!y) return x;
        /* Now x and y are not empty. */

        if(y->val < x->val) std::swap(x,y); // Smaller as x
        x->rs = merge(x->rs,y); // Merge shorter rs with y.

        if(!x->ls || x->ls->dist < x->rs->dist)
            std::swap(x->ls,x->rs); // ls should be longer than rs

        x->dist = x->rs ? x->rs->dist + 1 : 1;
        return x;
    }

    /**
     * @brief Allocate one element and construct it.
     * 
     * @param ls The left  son of given node.
     * @param rs The right son of given node.
     * @param dist The distance of given node.
     * @param objs The params to construct 
     * @return node* The address of newly-allocated and constructed node.
     */
    template <class ...Args>
    inline pointer alloc(pointer ls,pointer rs,size_t dist,Args &&...objs) {
        pointer temp = _Alloc.allocate();
        _Alloc.construct(temp,ls,rs,dist,std::forward <Args> (objs)...);
        return temp;
    }

    /* Deallocate one element. */
    void dealloc(pointer cur) noexcept { _Alloc.deallocate(cur); }

    /* Copy node info from cur node. */
    pointer copy(pointer cur) {
        if(!cur) return nullptr;
        return alloc(copy(cur->ls),copy(cur->rs),cur->dist,cur->val);
    }

    /* Remove current node with its sub-tree */
    void remove(pointer cur) {
        if(!cur) return;
        remove(cur->ls);
        remove(cur->rs);
        this->dealloc(cur);
    }

  public:

    /* Emptized. */
    heap() noexcept : _Alloc(),root(nullptr) {}
    /* Copy content. */
    heap(const heap &rhs) : _Alloc(rhs._Alloc),root(copy(rhs.root)) {}
    /* Move content. */
    heap(heap &&rhs) noexcept : _Alloc(rhs._Alloc),root(rhs.root) 
    { rhs.root = nullptr; }

    /* Now heap is re-initialized to empty. */
    ~heap() noexcept { clear(); }

    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            remove(root);
            root = copy(rhs.root);
            _Alloc = rhs._Alloc;
        }
        return *this;
    }

    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            this->~heap();
            std::swap(root,rhs.root);
            _Alloc = rhs._Alloc;
        }
        return *this;
    }

    /* Clean all the elements. */
    void clear() noexcept { remove(root); root = nullptr; }

    /* Return const reference to the smallest element. */
    const value_t &top() const { return root->val; }

    /* Push one element to the heap. */
    template <class ...Args>
    void emplace(Args &&...objs) 
    { root = merge(root,alloc(nullptr,nullptr,1,std::forward <Args> (objs)...)); }

    void push(value_t &&obj) 
    { root = merge(root,alloc(nullptr,nullptr,1,std::move(obj))); }

    void push(const value_t &obj) 
    { root = merge(root,alloc(nullptr,nullptr,1,obj)); }

    /* Pop out the top element. */
    void pop() {
        if(!root) return; /* Empty tree. */
        node *temp = root;
        root = merge(root->ls,root->rs);
        dealloc(temp);
    }

    bool empty()  const noexcept { return !root; }
    size_t size() const noexcept { return _Alloc.size(); }

  private:
    struct node {
        pointer ls;
        pointer rs;
        size_t dist;
        value_t val;
        template <class ...Args>
        node(pointer _l,pointer _r,size_t _d,Args &&...objs):
            ls(_l),rs(_r),dist(_d),
            val(std::forward <Args> (objs)...) {}
        ~node() = default;
    };

};



}


#endif
