#ifndef _DARK_HEAP_H_
#define _DARK_HEAP_H_


#include <cstddef>
#include <memory>


namespace dark {

constexpr size_t HEADER_OF_HEAP = 0;

template <class value_t>
struct heap_node {
    size_t dist;
    heap_node *ls;
    heap_node *rs;
    value_t val;
    template <class ...Args>
    heap_node(size_t _d,heap_node *_l,heap_node *_r,Args &&...objs):
        dist(_d),ls(_l),rs(_r),
        val(std::forward <Args> (objs)...) {}
    ~heap_node() = default;
};

using value_t = size_t;

class heap : protected std::allocator <heap_node <value_t> > {
  public:
    using node = heap_node <value_t>;
  
  protected:


    /* Special node with its distance as exactly 0. */
    static node *const null;
    node *root;
    size_t count;


    /* Merge 2 nodes. */
    static node *merge(node *x,node *y) {
        if(x == null) return y;
        if(y == null) return x;
        if(y->val < x->val) std::swap(x,y); // Smaller
        x->rs = merge(x->rs,y);
        if(x->ls->dist < x->rs->dist)
            std::swap(x->ls,x->rs);
        x->dist = x->rs->dist + 1;
        return x;
    }


    /* Alloc one element and construct it. */
    template <class ...Args>
    node *alloc(size_t dist,node *ls,node *rs,Args &&...objs) {
        node *temp = this->allocate(1);
        this->construct(temp,dist,ls,rs,std::forward <Args> (objs)...);
        return temp;
    }


    /* Dealloc one element. */
    void dealloc(node *temp) {
        this->destroy(temp);
        this->deallocate(temp,1);
    }


    /* Copy node info from target. */
    node *copy(node *target) {
        if(target == null) return null;
        return alloc(target->dist,
                    copy(target->ls),
                    copy(target->rs),
                    target->val);
    }


    /* Remove the node. */
    void remove(node *target) {
        if(target == null) return;
        remove(target->ls);
        remove(target->rs);
        dealloc(target);
    }

  public:
    /* Emptized. */
    heap() noexcept : root(null),count(0) {}
    /* Move content. */
    heap(heap &&rhs) noexcept : root(rhs.root) , count(rhs.count) {
        rhs.root  = null;
        rhs.count = 0;
    }
    /* Copy content. */
    heap(const heap &rhs) {
        root  = copy(rhs.root);
        count = rhs.count; 
    }

    /* Removal. */
    ~heap() noexcept {
        if(root == null) return;
        remove(root);
        count = 0;
    }

    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            this->~heap();
            this->construct(this,std::move(rhs));
        }
        return *this;
    }
    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            this->~heap();
            this->construct(this,rhs);
        }
        return *this;
    }


    /* Return const reference to the smallest element. */
    const value_t &top() const { return root->val; }

    /* Push one element to the heap. */
    template <class ...Args>
    void push(Args &&...objs) {
        ++count;
        root = merge(root,alloc(1,null,null,std::forward <Args> (objs)...));
    }

    /* Pop out the top element. */
    void pop() {
        if(root == null) return;
        --count;
        node *temp = root;
        root = merge(root->ls,root->rs);
        dealloc(temp);
    }

    bool empty()  const noexcept { return count; }
    size_t size() const noexcept { return count; }

};


heap::node *const heap::null = (heap::node *)(&HEADER_OF_HEAP);

}

#endif
