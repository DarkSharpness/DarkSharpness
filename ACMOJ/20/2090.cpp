#ifndef SRC_HPP
#define SRC_HPP

#include <stdexcept>
#include <initializer_list>

namespace sjtu {

class magic_base {
  protected:
    using typeinfo = unsigned long long;
    inline static typeinfo cnt = 0;
    friend class any_ptr;
};

template <class T>
class magic : magic_base {
    inline static void remove(void *ptr) {
        return delete static_cast<T *> (ptr);
    }
    static typeinfo get_id() { static const typeinfo id = ++cnt; return id; }
    friend class any_ptr;
};


class any_ptr {
public:
    using size_t = unsigned long long;
    using func_t = void (*)(void *);

    struct node {
        void * data;
        size_t refs;    // Reference count
        func_t deleter;
    };

    node * data {};
    any_ptr() noexcept = default;

    /**
     * @brief 拷贝构造函数，要求拷贝的层次为浅拷贝，即该对象与被拷贝对象的内容指向同一块内存
     * @note 若将指针作为参数传入，则指针的生命周期由该对象管理
     * @example
     *  any_ptr a = make_any_ptr(1);
     *  any_ptr b = a;
     *  a.unwrap<int> = 2;
     *  std::cout << b << std::endl; // 2
     * @param other
     */
    any_ptr(const any_ptr &other) noexcept {
        if ((data = other.data)) ++data->refs;
    }

    template <class T>
    any_ptr(T *ptr) {
        data = new node {
            .data       = ptr,
            .refs       = 1,
            .deleter    = magic<T>::remove
        };
    }

    ~any_ptr() {
        if (data && --data->refs == 0) {
            data->deleter(data->data);
            delete data;
        }
    }

    /**
     * @brief 拷贝赋值运算符，要求拷贝的层次为浅拷贝，即该对象与被拷贝对象的内容指向同一块内存
     * @note 应与指针拷贝赋值运算符的语义相近
     * @param other
     * @return any_ptr&
     */
    any_ptr &operator = (const any_ptr &other) {
        if (this != &other) {
            this->~any_ptr();
            ::new (this) any_ptr(other);
        } return *this;
    }

    template <class T>
    any_ptr &operator = (T *ptr) {
        this->~any_ptr();
        ::new (this) any_ptr(ptr);
    }

    template <class T>
    T &cast() const {
        if (data->deleter != magic<T>::remove)
            throw std::bad_cast();
        return *static_cast <T *> (data->data);
    }

    /**
     * @brief 获取该对象指向的值的引用
     * @note 若该对象指向的值不是 T 类型，则抛出异常 std::bad_cast
     * @example
     *  any_ptr a = make_any_ptr(1);
     *  std::cout << a.unwrap<int>() << std::endl; // 1
     * @tparam T
     * @return T&
     */
    template <class T>
    T &unwrap() { return this->cast <T> (); }

    template <class T>
    const T &unwrap() const { return this->cast <T> (); }
};

/**
 * @brief 由指定类型的值构造一个 any_ptr 对象
 * @example
 *  any_ptr a = make_any_ptr(1);
 *  any_ptr v = make_any_ptr<std::vector<int>>(1, 2, 3);
 *  any_ptr m = make_any_ptr<std::map<int, int>>({{1, 2}, {3, 4}});
 * @tparam T
 * @param t
 * @return any_ptr
 */
template <class T>
any_ptr make_any_ptr(const T &t) { return any_ptr(new T(t)); }

// 某些 any_ptr 类对象可能由不定长参数或初始化列表构造，请你参照上方的 example 补充 make_any_ptr 函数，我们会有一个特殊的测试点测试你的程序是否完成要求
template <class T, class... Args>
any_ptr make_any_ptr(Args &&... args) { return any_ptr({new T(std::forward<Args>(args)...)}); }
template <class T, class V>
any_ptr make_any_ptr(std::initializer_list <V> list) { return any_ptr(new T(std::move(list))); }

} // namespace sjtu

#endif
