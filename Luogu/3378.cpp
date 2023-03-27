#include <bits/stdc++.h>
#include <Dark/inout>

namespace dark {



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

    pointer   root;    /* Root node of the tree. */
    implement impl;

    /* Merge 2 nodes x and y. */
    pointer merge(pointer x,pointer y) {
        if(!x) return y;
        if(!y) return x;
        /* Now x and y are not empty. */

        if(impl(y->val,x->val)) std::swap(x,y); // Smaller as x
        x->rs = merge(x->rs,y); // Merge shorter rs with y.

        if(!x->ls || x->ls->dist < x->rs->dist)
            std::swap(x->ls,x->rs); // ls should be longer than rs

        x->dist = x->rs ? x->rs->dist + 1 : 1;
        return x;
    }

    /* Copy node info from target node. */
    pointer copy(pointer target) {
        if(!target) return nullptr;
        return impl.alloc(copy(target->ls),copy(target->rs),target->dist,target->val);
    }

    /* Remove target node with its sub-tree.(No destruction.) */
    void remove(pointer target) {
        if(!target) return;
        remove(target->ls);
        remove(target->rs);
        impl.dealloc(target);
    }

  public:

    /* Emptized. */
    heap() noexcept : root(nullptr) {}
    /* Copy content. */
    heap(const heap &rhs) : root(copy(rhs.root)) {}

    /* Move content. */
    heap(heap &&rhs) noexcept : root(rhs.root),impl(rhs.impl) 
    { rhs.root = nullptr; rhs.impl.count = 0; }

    /* Now heap is re-initialized to empty. */
    ~heap() noexcept { clear(); }

    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            clear(); /* Recycle nodes. */
            root = copy(rhs.root);
        }
        return *this;
    }

    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            clear(); /* Recycle nodes. */
            std::swap(root,rhs.root);
        }
        return *this;
    }

    /* Clean all the elements. */
    void clear() noexcept { remove(root); root = nullptr; }

    /* Return const reference to the smallest element. */
    const value_t &top() const { return root->val; }

    /* Push one element to the heap. */
    template <class ...Args>
    void emplace(Args &&...objs) {
        root = merge(root,impl.alloc(nullptr,nullptr,1,std::forward <Args> (objs)...));
    }

    /* Push one element to the heap. */
    void push(value_t &&obj) {
        root = merge(root,impl.alloc(nullptr,nullptr,1,std::move(obj)));
    }

    /* Push one element to the heap. */
    void push(const value_t &obj) {
        root = merge(root,impl.alloc(nullptr,nullptr,1,obj));
    }

    /* Pop out the top element. */
    void pop() {
        if(!root) return; /* Empty tree. */
        pointer temp = root;
        root = merge(root->ls,root->rs);
        impl.dealloc(temp);
    }

    /* Merge 2 heaps. */
    void merge(heap &rhs) {
        root = merge(root,rhs.root);
        impl.count += rhs.size();
        rhs.root = nullptr;
        rhs.impl.count = 0;
    }

    bool empty()  const noexcept { return !root; }
    size_t size() const noexcept { return impl.count; }

};


}


signed main() {
    dark::heap <int> x;
    int n = dark::read <int> ();
    while(n--) {
        char opt = dark::read_char();
        if(opt == '1') {
            x.push(dark::read <size_t> ());
        } else if(opt == '2') {
            dark::writeline(x.top());
        } else if(opt == '3') {
            x.pop();
        } else break;
    }
    return 0;
}