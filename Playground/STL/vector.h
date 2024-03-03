#pragma once
#include <memory>
#include <ranges>
#include <utility>
#include <concepts>
#include <algorithm>

namespace dark {

namespace vector_detail {

template <class _Tp, bool _Const>
struct iterator {
  private:
    using Node_t = std::conditional_t <_Const, const _Tp, _Tp>;
    Node_t *node {};    // Default initialized to nullptr.

  public:
    using value_type = _Tp;
    using difference_type = std::ptrdiff_t;
    using pointer = std::conditional_t <_Const, const _Tp*, _Tp*>;
    using reference = std::conditional_t <_Const, const _Tp&, _Tp&>;
    using iterator_category = std::contiguous_iterator_tag;

    Node_t *base() const { return node; }

    iterator() = default;
    explicit iterator(Node_t* _node) : node(_node) {}

    template <void * = nullptr> requires _Const
    iterator(iterator <_Tp, false> other) : node(other.node) {}

    /* Value accsssing. */

    Node_t &operator* () const { return *node; }
    Node_t *operator->() const { return  node; }
    Node_t &operator[] (std::ptrdiff_t __n) const { return node[__n]; }

    /* Self inc/decrement. */

    iterator &operator ++() { ++node; return *this; }
    iterator &operator --() { --node; return *this; }
    iterator operator ++(int) { iterator tmp = *this; ++*this; return tmp; }
    iterator operator --(int) { iterator tmp = *this; --*this; return tmp; }

    iterator &operator += (std::ptrdiff_t __n) { node += __n; return *this; }
    iterator &operator -= (std::ptrdiff_t __n) { node -= __n; return *this; }

    /* Pointer arithmetic */

    friend auto operator + (iterator __iter, std::ptrdiff_t n)
    -> iterator { return __iter += n; }
    friend auto operator + (std::ptrdiff_t n, iterator __iter)
    -> iterator { return __iter += n; }
    friend auto operator - (iterator __iter, std::ptrdiff_t n)
    -> iterator { return __iter -= n; }

    /* Pointer difference */

    friend auto operator - (iterator __iter1, iterator __iter2)
    -> std::ptrdiff_t { return __iter1.node - __iter2.node; }
};

template <class _Tp, bool _C1, bool _C2>
auto operator == (iterator <_Tp, _C1> __iter1, iterator <_Tp, _C2> __iter2)
-> bool { return __iter1.base() == __iter2.base(); }

template <class _Tp, bool _C1, bool _C2>
auto operator <=> (iterator <_Tp, _C1> __iter1, iterator <_Tp, _C2> __iter2)
-> decltype(__iter1.base() <=> __iter2.base()) {
    return __iter1.base() <=> __iter2.base();
}

template <class _Tp, class ..._Args>
requires (sizeof...(_Args) == 0)
_Tp &forward_only(_Tp &&__value, _Args &&...) { return std::forward <_Tp> (__value); }

template <class _Tp, class ..._Args>
struct __can_assign_helper {
    static constexpr bool __value = false;
};
template <class _Tp, class _Up, class ...Args>
struct __can_assign_helper <_Tp, _Up, Args...> {
    static constexpr bool __value =
        std::is_assignable_v <_Tp, _Up> && sizeof...(Args) == 0;
};

template <class _Tp, class ...Args>
concept __can_assign = __can_assign_helper <_Tp, Args...>::__value;


} // namespace detail


template <class _Tp>
struct vector {
  public:

    using value_type = _Tp;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = vector_detail::iterator <_Tp, false>;
    using const_iterator = vector_detail::iterator <_Tp, true>;

  protected:
    using Alloc_t = std::allocator <_Tp>;

    [[no_unique_address]] Alloc_t alloc;  // Allocator for the storage.

    _Tp *head;  // Pointer to the first element.
    _Tp *tail;  // Pointer to the last element + 1.
    _Tp *term;  // Pointer to the terminal of the storage.

    /* Initialize with a size of n elements. */
    vector(std::size_t __n, std::nullptr_t) : alloc() {
        head = alloc.allocate(__n);
        term = tail = head + __n;
    }

    /* Clean the storage only. */
    void clean_storage(std::size_t __n, std::size_t __m) {
        std::ranges::destroy_n(head, __n);
        alloc.deallocate(head, __m);
    }

    /* Clean the storage only. */
    void clean_storage() { return this->clean_storage(this->size(), this->capacity()); }

    /* Reserve space for exactly one element. */
    void push_reserve() {
        if (tail == term) {
            const std::size_t __m = this->size();
            const std::size_t __n = __m << 1 | (__m == 0);
            auto *__temp = alloc.allocate(__n);  // New head.
            term = __temp + __n;                // New terminal.

            std::uninitialized_move_n(head, __m, __temp);
            this->clean_storage(__m, __m);

            head = __temp;
            tail = __temp + __m;
        }
    }

    template <typename _Iter>
    void assign_grow(_Iter __beg, std::size_t __n) {
        this->clean_storage();
        head = alloc.allocate(__n);
        term = tail = head + __n;
        std::uninitialized_copy_n(__beg, __n, head);
    }

    template <typename _Iter>
    void assign_and_remove(_Iter __beg, std::size_t __n) {
        auto __tail = std::ranges::copy_n(__beg, __n, head).out;
        const std::size_t __m = tail - __tail;
        tail = __tail;
        std::ranges::destroy_n(tail, __m);
    }

    template <typename _Iter>
    void assign_and_insert(_Iter __beg, std::size_t __n) {
        if (this->capacity() < __n) return assign_grow(__beg, __n);
        const std::size_t __a = this->size();   // Assign
        const std::size_t __c = __n - __a;      // Construct

        /* First, assign for those initialized. */
        auto [__mid, __temp] = std::ranges::copy_n(__beg, __a, head);

        /* Then, construct for the rest. */
        tail = std::uninitialized_copy_n(__mid, __c, __temp);
    }

    _Tp *emplace_grow(_Tp *__pos) {
        const std::size_t __m = this->size();
        const std::size_t __n = __m << 1 | (__m == 0);
        auto *__temp = alloc.allocate(__n); // New head.
        term = __temp + __n;
    
        auto __iter = std::uninitialized_move(head, __pos, __temp);
        auto __tail = std::uninitialized_move(__pos, tail, __iter + 1);

        const std::size_t __r = this->size();
        this->clean_storage(__r, __r);

        head = __temp;
        tail = __tail;

        return __iter;
    }

  public:

    vector() noexcept : head(), tail(), term() {}

    vector(std::size_t __n) : vector(__n, nullptr) {
        std::ranges::uninitialized_default_construct_n(head, __n);
    }

    vector(std::size_t __n, const _Tp &__value) : vector(__n, nullptr) {
        std::ranges::uninitialized_fill_n(head, __n, __value);
    }

    vector(std::initializer_list <_Tp> __list) : vector(__list.size(), nullptr) {
        std::uninitialized_copy(__list.begin(), __list.end(), head);
    }

    vector(const vector &other) : vector(other.size(), nullptr) {
        std::uninitialized_copy(other.head, other.tail, head);
    }

    vector(vector &&other) noexcept
        : head(other.head), tail(other.tail), term(other.term) {
        other.head = other.tail = other.term = nullptr;
    }

    ~vector() { clean_storage(); }

  public:

    std::size_t size() const noexcept { return tail - head; }
    std::size_t capacity() const noexcept { return term - head; }
    bool empty() const noexcept { return head == tail; }

    vector &operator = (const vector &other) {
        if (this != &other) {
            const std::size_t __n = other.size();
            if (this->size() < __n) {
                assign_and_remove(other.head, __n);
            } else {
                assign_and_insert(other.head, __n);
            }
        } return *this;
    }

    vector &operator = (vector &&other) noexcept { this->swap(other); }

    void push_back(const _Tp &__value) {
        push_reserve();
        std::construct_at(tail++, __value);
    }

    void push_back(_Tp &&__value) {
        push_reserve();
        std::construct_at(tail++, std::move(__value));
    }

    template <typename ..._Args>
    iterator emplace_back(_Args &&...__args) {
        push_reserve();
        std::construct_at(tail++, std::forward <_Args>(__args)...);
        return iterator { tail - 1 };
    }

    void pop_back() noexcept { std::destroy_at(--tail); }

    template <typename ..._Args>
    iterator emplace(iterator __pos, _Args &&...__args) {
        auto *__ptr = __pos.base();
        if (__ptr == tail) return emplace_back(std::forward <_Args>(__args)...);
        if (tail == term) {
            auto *__iter = emplace_grow(__ptr);
            std::construct_at(__iter, std::forward <_Args> (__args)...);
            return iterator { __iter };
        }

        /* Insert at non-end position, no-reallocate. */
        auto __old = tail++;
        std::construct_at(__old, std::move(*(__old - 1)));
        std::ranges::move_backward(__ptr, __old - 1, __old);

        using namespace vector_detail;

        if constexpr (__can_assign <_Tp, _Args...>) {
            *__ptr = forward_only(std::forward <_Args>(__args)...);
        } else {
            std::destroy_at(__ptr);
            std::construct_at(__ptr, std::forward <_Args>(__args)...);
        }

        std::destroy_at(__ptr);
        std::construct_at(__ptr, std::forward <_Args>(__args)...);

        return iterator { __pos };
    }

    iterator insert(iterator __pos, const _Tp &__value)
    { return emplace(__pos, __value); }

    iterator insert(iterator __pos, _Tp &&__value)
    { return emplace(__pos, std::move(__value)); }

    iterator erase(iterator __pos) {
        auto *__ptr = __pos.base();
        std::ranges::move(__ptr + 1, tail, __ptr);
        std::destroy_at(--tail);
        return iterator { __ptr };
    }

    void clear() noexcept { std::destroy_n(head, size()); tail = head; }

    void swap(vector &other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(term, other.term);
    }

  public:
    reference at(std::size_t __n) {
        if (__n >= this->size()) throw std::out_of_range("vector::at");
        return head[__n];
    }
    const_reference at(std::size_t __n) const {
        if (__n >= this->size()) throw std::out_of_range("vector::at");
        return head[__n];
    }

    reference operator [] (std::size_t __n) noexcept { return head[__n]; }
    const_reference operator [] (std::size_t __n) const noexcept { return head[__n]; }

    reference front() noexcept { return *begin(); }
    reference back()  noexcept { return *--end(); }
    const_reference front() const noexcept { return *begin(); }
    const_reference back()  const noexcept { return *--end(); }

    iterator begin() noexcept { return iterator {head}; }
    iterator end()   noexcept { return iterator {tail}; }

    const_iterator begin()  const noexcept { return const_iterator {head}; }
    const_iterator end()    const noexcept { return const_iterator {tail}; }
    const_iterator cbegin() const noexcept { return const_iterator {head}; }
    const_iterator cend()   const noexcept { return const_iterator {tail}; }
};


} // namespace dark

namespace std {

template <class _Tp>
void swap(dark::vector <_Tp> &__x, dark::vector <_Tp> &__y)
noexcept { __x.swap(__y); }


} // namespace std

namespace sjtu {

using dark::vector;

} // namespace sjtu
