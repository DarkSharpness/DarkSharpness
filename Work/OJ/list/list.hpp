#pragma once
#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include <memory>
#include <cstddef>

namespace sjtu {


/**
 * @tparam T Type of the elements.
 * Be careful that T may not be default constructable.
 * 
 * @brief A list that supports operations like std::list.
 * 
 * We encourage you to design the implementation yourself.
 * As for the memory management, you may use std::allocator,
 * new/delete, malloc/free or something else.
*/
template <typename T>
class list {
  public:
    class iterator;
    class const_iterator;

  public:

    /**
     * Constructs & Assignments
     * At least three: default constructor, copy constructor/assignment
     * Bonus: move/initializer_list constructor/assignment
     */
    list() {}
    list(const list &other) {}
    list &operator=(const list &other) {}

    /* Destructor. */
    ~list() {}

    /* Access the first / last element. */
    T &front() noexcept {}
    T &back()  noexcept {}
    const T &front() const noexcept {}
    const T &back()  const noexcept {}

    /* Return an iterator pointing to the first element. */
    iterator begin() noexcept {}
    const_iterator cbegin() const noexcept {}

    /* Return an iterator pointing to one past the last element. */
    iterator end() noexcept {}
    const_iterator cend() const noexcept {}

    /* Checks whether the container is empty. */
    bool empty() const noexcept {}
    /* Return count of elements in the container. */
    size_t size() const noexcept {}

    /* Clear the contents. */
    void clear() noexcept {}

    /**
     * @brief Insert value before pos (pos may be the end() iterator).
     * @return An iterator pointing to the inserted value.
     * @throw Throw if the iterator is invalid.
     */
    iterator insert(iterator pos, const T &value) {}

    /**
     * @brief Remove the element at pos (remove end() iterator is invalid).
     * @return An iterator pointing to the following element, if pos pointing to
     * the last element, end() will be returned.
     * @throw Throw if the container is empty, or the iterator is invalid.
     */
    iterator erase(iterator pos) noexcept {}

    /* Add an element to the front/back. */
    void push_front(const T &value) {}
    void push_back (const T &value) {}

    /* Removes the first/last element. */
    void pop_front() noexcept {}
    void pop_back () noexcept {}

  public:

    /**
     * Basic requirements:
     * operator ++, --, *, ->
     * operator ==, != between iterators and const iterators
     * constructing a const iterator from an iterator
     * 
     * If your implementation meets these requirements,
     * you may not comply with the following template.
     * You may even move this template outside the class body,
     * as long as your code works well.
     * 
     * Contact TA whenever you are not sure.
     */
    class iterator {
      private:
        /**
         * TODO just add whatever you want.
         */

      public:
        iterator &operator++()  {}
        iterator &operator--()  {}
        iterator operator++(int) {}
        iterator operator--(int) {}

        T &operator*()  const noexcept {}
        T *operator->() const noexcept {}

        /* A operator to check whether two iterators are same (pointing to the same memory) */
        friend bool operator == (const iterator &a, const iterator &b) {}
        friend bool operator != (const iterator &a, const iterator &b) {}
    };

    /**
     * Const iterator should have same functions as iterator, just for a const object.
     * It should be able to construct from an iterator.
     * It should be able to compare with an iterator.
     */
    class const_iterator {};
};

} // namespace sjtu

#endif // SJTU_LIST_HPP
