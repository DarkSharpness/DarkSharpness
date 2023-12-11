#pragma once
#include <new>
#include <utility>
// 你不可以使用其他任何头文件

namespace sjtu {

/**
 * @brief 一个可以在离开作用域之后自动归还内存的指针。
 * unique_ptr <_Tp> 行为应该和普通指针 _Tp * 几乎一致。
 * @tparam _Tp 模板参数，指针指向的类型。
 */
template <typename _Tp>
class unique_ptr {
  private:
    _Tp *ptr {}; // 初始化为空
  public:
    unique_ptr() noexcept = default;
    ~unique_ptr() { delete ptr; }

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &&other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
    unique_ptr &operator=(unique_ptr &&other) noexcept {
        if (this != &other) {
            this->~unique_ptr();
            ::new (this) unique_ptr(std::move(other));
        }
        return *this;
    }

    explicit unique_ptr(_Tp *other) noexcept : ptr(other) {}

    void reset()   noexcept { delete ptr; ptr = nullptr; }
    _Tp *release() noexcept { _Tp *tmp = ptr; ptr = nullptr; return tmp; }
    _Tp *get() const noexcept { return ptr; }

    _Tp &operator* () noexcept { return *ptr; }
    _Tp *operator->() noexcept { return  ptr; }
};

template <typename _Tp, typename... Args>
unique_ptr <_Tp> make_unique(Args &&... args) {
    return unique_ptr <_Tp> (new _Tp(std::forward<Args>(args)...));
}

} // namespace sjtu
