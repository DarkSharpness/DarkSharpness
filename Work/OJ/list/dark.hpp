#pragma once
#include <memory>
#include <cstddef>

namespace dark {

namespace list_detail {

struct node_base {
    union {
        node_base *link[2];
        struct {
            node_base *next;
            node_base *prev;
        };
    };
};


template <typename _Tp>
struct list_node : public node_base { _Tp data; };

template <typename _Tp, bool _Const>
struct iterator {
  private:
    using Base_t    = std::conditional_t<_Const, const node_base, node_base>;
    using Node_t    = std::conditional_t<_Const, const list_node <_Tp>, list_node <_Tp>>;
    using Value_t   = std::conditional_t<_Const, const _Tp, _Tp>;

    Base_t *node {}; // Default initialization to nullptr.

  public:
    Node_t *base() const noexcept { return static_cast <Node_t *> (node); }

    iterator() noexcept = default;
    explicit iterator(Base_t *data) noexcept : node(data) {}

    /* Just to allow construction from non-const to const. */
    template <void * = nullptr> requires _Const
    iterator(iterator<_Tp, false> other) noexcept : node(other.base()) {}

    template <void * = nullptr> requires _Const
    iterator <_Tp, false> remove_const() const noexcept {
        return iterator <_Tp, false> { const_cast <node_base *> (node) };
    }

    Value_t &operator*  ()  const noexcept  { return  base()->data; }
    Value_t *operator-> ()  const noexcept  { return &base()->data; }

    iterator &operator++() noexcept {
        node = node->next;
        return *this;
    }
    iterator &operator--() noexcept {
        node = node->prev;
        return *this;
    }
    iterator operator++(int) noexcept {
        iterator tmp = *this;
        ++*this;
        return tmp;
    }
    iterator operator--(int) noexcept {
        iterator tmp = *this;
        --*this;
        return tmp;
    }
};

template <typename _Tp, bool _C1, bool _C2>
inline bool operator == (iterator<_Tp, _C1> a, iterator<_Tp, _C2> b)
noexcept {  return a.base() == b.base();  }

/* Link 2 nodes , and return successive node. */
inline node_base *link(node_base *__prev, node_base *__next)
noexcept {
    __prev->next = __next;
    __next->prev = __prev;
    return __next;
}

/* Insert a node into 2 nodes. */
inline void insert(node_base *__prev, node_base *__next, node_base *__node)
noexcept { link(__prev, __node); link(__node, __next); }

} // namespace list_detail


/**
 * @tparam _Tp Type of the elements.
 * @brief A list that supports operations like std::list.
*/
template <typename _Tp>
class list {
  public:
    using iterator          = list_detail::iterator<_Tp, false>;
    using const_iterator    = list_detail::iterator<_Tp, true>;

  protected:
    using Node_t    = list_detail::list_node<_Tp>;
    using Base_t    = list_detail::node_base;
    using Alloc_t   = std::allocator<Node_t>;
    using Header_t  = list_detail::list_node<size_t>;

    Header_t head;
    [[no_unique_address]] Alloc_t alloc {};

  protected:

    void inc_size(size_t __size) noexcept { head.data += __size; }
    void set_size(size_t __size) noexcept { head.data  = __size; }

    template <typename ..._Args>
    Node_t *create_node(_Args &&...args) {
        Node_t *tmp = alloc.allocate(1);
        std::construct_at(&tmp->data, std::forward<_Args>(args)...);
        return tmp;
    }

    template <typename ..._Args>
    void destroy_node(Node_t *node) noexcept {
        std::destroy_at(&node->data);
        alloc.deallocate(node, 1);
    }

    iterator insert_after(iterator __pos, Node_t *__node) {
        Base_t *__prev = __pos.base();
        Base_t *__next = __prev->next;
        list_detail::insert(__prev, __next, __node);
        return iterator { __node };
    }
    iterator insert_before(iterator __pos, Node_t *__node) {
        Base_t *__next = __pos.base();
        Base_t *__prev = __next->prev;
        list_detail::insert(__prev, __next, __node);
        return iterator { __node };
    }

    template <bool _Resize, typename _Iter>
    iterator insert_range(iterator __pos, _Iter __beg, _Iter __end) {
        if (__beg == __end) return __pos;   // Nothing to insert.

        Base_t *__node  = __pos.base();
        Base_t *__prev  = __node->prev;
        size_t  __size  = 0;

        do { /* At least one element inserted. */
            if constexpr (_Resize) ++__size;
            Node_t *__temp = create_node(*__beg++);
            list_detail::link(__prev, __temp);
            __prev = __temp;
        } while (__beg != __end);

        if constexpr (_Resize) inc_size(__size);
        list_detail::link(__prev, __node);
        return iterator { __node };
    }

    template <bool _Resize>
    iterator remove_range(iterator __beg, iterator __end) noexcept {
        if (__beg == __end) return __end;

        Base_t *__prev  = __beg.base()->prev;
        Base_t *__node  = __end.base();
        size_t  __size  = 0;

        do { /* At least one element inserted. */
            if constexpr (_Resize) ++__size;
            Node_t *__temp = (__beg++).base();
            destroy_node(__temp);
        } while (__beg != __end);

        if constexpr (_Resize) inc_size(__size);
        list_detail::link(__prev, __node);
        return iterator { __node };
    }

    template <typename _Iter>
    void assign_and_insert(_Iter __beg, _Iter __end) {
        for (auto &val : *this) val = *__beg++;
        insert_range <false> (this->end(), __beg, __end);
    }

    template <typename _Iter>
    void assign_and_remove(_Iter __beg, _Iter __end) {
        iterator __cur = this->begin();
        while (__beg != __end) *__cur++ = *__beg++;
        remove_range <false> (__cur, this->end());
    }

    void clean_up() noexcept {
        Base_t *__cur = head.next;
        while (__cur != &head) {
            Base_t *__tmp = __cur;
            __cur = __cur->next;
            destroy_node(static_cast <Node_t *> (__tmp));
        }
    }

  public:

    list() noexcept {
        set_size(0);
        list_detail::link(&head, &head);
    }

    list(const list &other) {
        set_size(other.size());
        head.prev = &head;
        insert_range <false> (this->end(), other.begin(), other.end());
    }

    list(list &&other) noexcept {
        set_size(other.size());
        other->set_size(0);
        if (this->size() == 0) {
            head.next = &head;
            head.prev = &head;
        } else {
            using list_detail::link;
            link(&head, other.head.next);
            link(other.head.prev, &head);
            link(&other.head, &other.head);
        }
    }

    list &operator = (const list &other) {
        if (this == &other) return *this;
        if (this->size() < other.size()) {
            set_size(other.size());
            assign_and_insert(other.begin(), other.end());
        } else {
            set_size(other.size());
            assign_and_remove(other.begin(), other.end());
        } return *this;
    }

    list &operator = (list &&other) {
        if (this == &other) return *this;
        this->~list();
        std::construct_at(this, std::move(other));
    }


    ~list() { clean_up(); }

    _Tp &front() noexcept { return *begin(); }
    _Tp &back()  noexcept { return *--end(); }
    const _Tp &front() const noexcept { return *begin(); }
    const _Tp &back()  const noexcept { return *--end(); }

    iterator begin()    noexcept { return iterator {  head.next }; }
    iterator end()      noexcept { return iterator {    &head   }; }
    const_iterator begin()  const noexcept { return const_iterator {  head.next }; }
    const_iterator end()    const noexcept { return const_iterator {    &head   }; }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend()   const noexcept { return end(); }

    bool empty()    const noexcept { return !head.data; }
    size_t size()   const noexcept { return  head.data; }

    void clear() noexcept {
        clean_up();
        std::construct_at(this);
    }

    void push_front(const _Tp &__val) {
        inc_size(1);
        insert_after(end(), create_node(__val));
    }
    void push_front(_Tp &&__val) {
        inc_size(1);
        insert_after(end(), create_node(std::move(__val)));
    }
    void push_back(const _Tp &__val) {
        inc_size(1);
        insert_before(end(), create_node(__val));
    }
    void push_back(_Tp &&__val) {
        inc_size(1);
        insert_before(end(), create_node(std::move(__val)));
    }

    void pop_front() noexcept {
        inc_size(-1);
        Node_t *__node = begin().base();
        list_detail::link(&head, __node->next);
        destroy_node(__node);
    }
    void pop_back () noexcept {
        inc_size(-1);
        Node_t *__node = (--end()).base();
        list_detail::link(__node->prev, &head);
        destroy_node(__node);
    }


    iterator insert(const_iterator pos, const _Tp &__val) {
        inc_size(1);
        return insert_before(pos.remove_const(), create_node(__val));
    }
    iterator insert(const_iterator pos, _Tp &&__val) {
        inc_size(1);
        return insert_before(pos.remove_const(), create_node(std::move(__val)));
    }

    iterator erase(const_iterator pos) noexcept {
        inc_size(-1);
        using list_detail::link;
        Node_t *__node = pos.remove_const().base();
        Base_t *__next = link(__node->prev, __node->next);
        destroy_node(__node);
        return iterator { __next };
    }

    template <typename _Iter>
    iterator insert(const_iterator __pos, _Iter __beg, _Iter __end) {
        return insert_range <true> (__pos.remove_const(), __beg, __end);
    }
    iterator erase(const_iterator __beg, const_iterator __end) noexcept {
        return remove_range <true> (__beg.remove_const(), __end.remove_const());
    }

};

} // namespace dark


namespace sjtu {

template <typename _Tp>
using list = dark::list <_Tp>;

} // namespace sjtu
