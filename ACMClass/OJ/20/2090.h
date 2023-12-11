#ifndef SRC_HPP
#define SRC_HPP

#include <functional>
#include <initializer_list>

namespace sjtu {

class any_ptr {
 public:
  /**
   * @brief 默认构造函数，行为应与创建空指针类似
   * 
   */
  any_ptr() {}

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
  any_ptr(const any_ptr &other) {}
  template <class T> any_ptr(T *ptr) {}

  /**
   * @brief 析构函数，注意若一块内存被多个对象共享，那么只有最后一个析构的对象需要释放内存
   * @example
   *  any_ptr a = make_any_ptr(1);
   *  {
   *    any_ptr b = a;
   *  }
   *  std::cout << a << std::endl; // valid
   * @example
   *  int *p = new int(1);
   *  any_ptr a = p;
    *  {
   */
  ~any_ptr() {}

  /**
   * @brief 拷贝赋值运算符，要求拷贝的层次为浅拷贝，即该对象与被拷贝对象的内容指向同一块内存
   * @note 应与指针拷贝赋值运算符的语义相近
   * @param other
   * @return any_ptr&
   */
  any_ptr &operator=(const any_ptr &other) {}
  template <class T> any_ptr &operator=(T *ptr) {}

  /**
   * @brief 获取该对象指向的值的引用
   * @note 若该对象指向的值不是 T 类型，则抛出异常 std::bad_cast
   * @example
   *  any_ptr a = make_any_ptr(1);
   *  std::cout << a.unwrap<int>() << std::endl; // 1
   * @tparam T
   * @return T&
   */
  template <class T> T &unwrap() {}
  // 某一个 any_ptr 类对象可能为 const，请你补充 unwrap 函数
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
template <class T> any_ptr make_any_ptr(const T &t) { return any_ptr(new T(t)); }

// 某些 any_ptr 类对象可能由不定长参数或初始化列表构造
// 请你参照上方的 example 补充 make_any_ptr 函数，我们会有一个特殊的测试点测试你的程序是否完成要求
// 特别提示，初始化列表类型的模板类型可能和最终指定的类型不同


}  // namespace sjtu

#endif