#ifndef _DARK_HEAP_H_
#define _DARK_HEAP_H_


#include <cstddef>
#include <memory>


namespace dark {


template <class value_t>
struct heap_node {
    heap_node *ls;
    heap_node *rs;
    size_t dist;
    value_t val;
    template <class ...Args>
    heap_node(heap_node *_l,heap_node *_r,size_t _d,Args &&...objs):
        ls(_l),rs(_r),dist(_d),
        val(std::forward <Args> (objs)...) {}
    ~heap_node() = default;
};


template <class value_t>
class heap : protected std::allocator <heap_node <value_t> > {
  protected:

    using node = heap_node <value_t>;


    /* Special node with its distance as exactly 0. */
    node * root;    /* Root node of the tree. */
    node * head;    /* Head of linked list of available elements. */
    node * tail;    /* Tail of linked list of available elements. */
    size_t count;   /* Count of all the elements. */


    /* Merge 2 nodes x and y. */
    static node *merge(node *x,node *y) {
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
    inline node *alloc(node *ls,node *rs,size_t dist,Args &&...objs) {
        node *temp; /* Node to be constructed on. */
        if(head) {
            temp = head;
            head = head->rs;
            if(!head) tail = nullptr; /* Empty list case. */

            temp->ls   = ls;
            temp->rs   = rs;
            temp->dist = dist;
            temp->val  = value_t(std::forward <Args> (objs)...);

        } else {
            temp = this->allocate(1);
            this->construct(temp,ls,rs,dist,std::forward <Args> (objs)...);
        }
        return temp;
    }


    /* Deallocate one element without destruction!. */
    void dealloc(node *target) {
        target->ls = nullptr;
        target->rs = head;
        if(head) head->ls = target;
        else         tail = target;
        head = target;
    }


    /* Copy node info from target node. */
    node *copy(node *target) {
        if(!target) return nullptr;
        return alloc(copy(target->ls),copy(target->rs),target->dist,target->val);
    }


    /* Remove target node with its sub-tree.(No destruction.) */
    void remove(node *target) {
        if(!target) return;
        remove(target->ls);
        remove(target->rs);
        this->dealloc(target);
    }

  public:

    /* Emptized. */
    heap() noexcept :
        root(nullptr),head(nullptr),tail(nullptr),count(0) {}
    /* Copy content. */
    heap(const heap &rhs) :
        head(nullptr),tail(nullptr),count(rhs.count) {
        root = copy(rhs.root);
    }
    /* Move content. */
    heap(heap &&rhs) noexcept : heap() {
        std::swap(root,rhs.root);
        std::swap(head,rhs.head);
        std::swap(tail,rhs.tail);
        std::swap(count,rhs.count);
    }


    /* Now heap is re-initialized to empty. */
    ~heap() noexcept {
        clear();
        shrink();
    }


    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            remove(root);
            root  = copy(rhs.root);
            count = rhs.count;
        }
        return *this;
    }


    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            clear(); /* Recycle nodes. */

            /* Link 2 list. */
            if(!tail) { /* LHS list empty. */
                std::swap(head,rhs.head);
                std::swap(tail,rhs.tail);
            } else if(rhs.head) { /* Both list not empty.*/
                rhs.head->ls = tail;
                tail     = rhs.tail;
                rhs.head = rhs.tail = nullptr;
            } /* RHS list empty only case. */

            /* Swap data. */
            std::swap(root,rhs.root);
            std::swap(count,rhs.count);
        }
        return *this;
    }

    /* Clean all the elements. */
    void clear() {
        remove(root);
        root  = nullptr;
        count = 0;
    }

    /* Clean the link-listed nodes.(With destruction) */
    void shrink() {
        while(head) {
            tail = head->rs;
            this->destroy(head);
            this->deallocate(head,1);
            head = tail;
        }
        /* Now head = tail = nullptr */
    }


    /* Return const reference to the smallest element. */
    const value_t &top() const { return root->val; }

    /* Push one element to the heap. */
    template <class ...Args>
    void emplace(Args &&...objs) {
        ++count;
        root = merge(root,alloc(nullptr,nullptr,1,std::forward <Args> (objs)...));
    }

    void push(value_t &&obj) {
        ++count;
        root = merge(root,alloc(nullptr,nullptr,1,std::move(obj)));
    }

    void push(const value_t &obj) {
        ++count;
        root = merge(root,alloc(nullptr,nullptr,1,obj));
    }

    /* Pop out the top element. */
    void pop() {
        if(!root) return; /* Empty tree. */
        --count;
        node *temp = root;
        root = merge(root->ls,root->rs);
        dealloc(temp);
    }

    bool empty()  const noexcept { return !root; }
    size_t size() const noexcept { return count; }

};



}


#endif
