#pragma once
#include <new>
#include <utility>
#include <stdexcept>
// 你不可以使用任何其他的头文件

namespace koishi {

class any {
  private:
    struct base;
    base *ptr = nullptr; // 指向基类的指针

    template <typename T>
    T *dyn_cast() const noexcept {
        auto *tmp = dynamic_cast <storage <T> *> (ptr);
        return tmp ? &tmp->value : nullptr;
    }

  public:
    any() noexcept = default;

    ~any() { delete ptr; }

    any(std::nullptr_t) : any() {}

    any(const any &other) : ptr(other.ptr ? other.ptr->clone() : nullptr) {}

    any(any &&other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }

    template <typename T, typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, any>>>
    any(T &&Arg) : ptr(new storage <std::decay_t<T>> (std::forward<T>(Arg))) {}

    template <typename T, typename ...Args>
    friend any make_any(Args &&...args) {
        any ret;        // 返回值
        ret.ptr = new any::storage <T> (std::forward <Args> (args)...);
        return ret;     // 特别提醒，不要对于返回的值(不是引用)使用 std::move()
    }

    any &operator = (const any &other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr ? other.ptr->clone() : nullptr;
        } return *this;
    }

    any &operator = (any &&other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        } return *this;
    }

    template <typename T>
    T &cast() {
        if (auto tmp = dyn_cast<T>()) return *tmp;
        throw std::bad_cast();
    }

    template <typename T>
    const T &cast() const {
        if (auto tmp = dyn_cast<T>()) return *tmp;
        throw std::bad_cast();
    }

    template <typename T>
    T *try_cast() { return dyn_cast<T>(); }

    // 差不多，但是是 const 版本的。
    template <typename T>
    const T *try_cast() const { return dyn_cast<T>(); }

    bool is_empty() const noexcept { return ptr == nullptr; }

  private:

    // 以下是 base 类和 storage 类的实现。
    // 你可以思考一下为什么要这么设计。
    // 事实上 any 类的设计并不唯一，标准库也并不是这么写的
    // 标准库使用函数指针那种写法，我觉得还是这种写法比较好理解些。

    struct base {
        virtual ~base() = default;
        virtual base *clone() const = 0;
    };

    template <typename T>
    struct storage : base {
        T value; // 真实的数据存储在这里哦

        // 完美转发，接受任意类型的参数
        template <typename Args>
        storage(Args &&args) : value(std::forward <Args>(args)) {}

        // 拷贝一份自己，返回基类的指针。
        base *clone() const override { return new storage(value); }
    };
};


} /* namespace koishi */

