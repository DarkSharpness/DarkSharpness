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

  public:
    // 构造一个空的指针 (nullptr)
    unique_ptr();

    // 同一个指针不能被多个 unique_ptr 指向
    unique_ptr(const unique_ptr &) = delete;

    // 移动构造函数。移交所有权。
    // 注意移交后要把 other 置空。
    unique_ptr(unique_ptr &&other);

    // 析构函数。释放指针指向的内存。
    // 需要注意，delete nullptr 是安全的。
    ~unique_ptr();

    // 同一个指针不能被多个 unique_ptr 指向
    unique_ptr &operator=(const unique_ptr &) = delete;

    // 移动赋值运算符。移交所有权。
    // 注意移交后要把 other 置空。
    unique_ptr &operator=(unique_ptr &&other);

    // 接管一个普通 _Tp 类型的指针的所有权
    explicit unique_ptr(_Tp *);

    // 重置为空指针。同时释放指针指向的内存。
    void reset();

    // 转移所有权，返回指针指向的对象的指针
    // 同时，自己要置空。
    _Tp *release();

    // 返回指针指向的对象的指针
    // 所有权不转移。
    _Tp *get() const;

    // 重载 * 运算符(解引用)，返回指针指向的对象的引用
    _Tp &operator*();

    // 重载 -> 运算符(成员访问)，返回指针指向的对象的地址
    _Tp *operator->();
};

// 对于一个 unique_ptr，你最多只能存一个指针
static_assert(sizeof(unique_ptr<int>) <= sizeof(void *)) ;

// 创建一个 unique_ptr，指向一个用 new 分配的 _Tp 对象
template <typename _Tp>
unique_ptr <_Tp> make_unique(const _Tp &);

// Bonus: (不作为考察内容)
// 可变长参数列表 + 万能引用
// 创建一个 unique_ptr，指向一个用 new 分配的 _Tp 对象
// 参数列表长度可变，且有左值引用和右值引用两种版本
// 当传入左值 T &， Args 类型被推导为 T &
// 当传入右值 T &&，Args 类型被推导为 T
// 你需要了解如何用 std::forward 实现完美转发
template <typename _Tp, typename... Args>
unique_ptr <_Tp> make_unique(Args &&... args);

} // namespace sjtu
