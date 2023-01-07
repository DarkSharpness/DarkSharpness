#include <iostream>

class Any {
  private:

    /* Base class */
    struct Base {
        virtual ~Base() = default;
        virtual Base *clone() const {return nullptr;}
    };

    template <typename T>
    struct Data : Base {
      public:

        T data;
        virtual ~Data() override = default;
        Data(T &&val) : data(std::move(val)) {}
        Data(const T &val) : data(val) {}
        virtual Base *clone() const override { return try_clone <> (); }

      private:

        /* Clone a copy-constructible object. */
        template <typename Q = T,
                  typename std::enable_if_t<std::is_copy_constructible<Q>::value, int> = 0>
        Base *try_clone() const {
            return new Data <T> (data);
        }

        /* Fail to clone , thus return nullptr. */
        template <typename Q = T,
                  typename std::enable_if_t<!std::is_copy_constructible<Q>::value, int> = 0>
        Base *try_clone() const {
            return nullptr;
        }
    };

    Base *ptr;
    

  public:
    ~Any() { delete ptr; }
    Any() : ptr(nullptr) {}
    Any(std::nullptr_t) : ptr(nullptr) {}


    template <typename U>
    Any(U &&val) : ptr( new Data <typename std::decay <U>::type> (std::forward <U> (val)) ) {}


    Any(Any &&rhs) : ptr(rhs.ptr) { rhs.ptr = nullptr; }
    Any(const Any &rhs) : ptr(rhs.ptr->clone()) {}


    Any &operator = (Any &&rhs) {
        if(this != &rhs) {
            this->~Any();
            ptr     = rhs.ptr;
            rhs.ptr = nullptr;
        }
        return *this;
    }

    Any &operator = (const Any &rhs) {
        if(this != &rhs) {
            this->~Any();
            ptr = rhs.ptr->clone();
        }
        return *this;
    }

    template <typename U>
    operator U() {
        return as <std::decay_t <U>>;
    }

    template <typename U>
    operator const U() const {
        return as <const std::decay_t <U>>;
    }

    template <typename U>
    bool is() const {
        using T = std::decay_t <U>;
        Data <T> *tmp = dynamic_cast <Data <T> *> (ptr);
        return tmp;
    }

    template <typename U>
    std::decay_t <U> &as() {
        using T = std::decay_t <U>;
        Data <T> *tmp = dynamic_cast <Data <T> *> (ptr);
        if(!tmp) throw std::bad_cast();
        return tmp->data;
    }

    template <typename U>
    const std::decay_t <U> &as() const {
        using T = std::decay_t <U>;
        Data <T> *tmp = dynamic_cast <Data <T> *> (ptr);
        if(!tmp) throw std::bad_cast();
        return tmp->data;
    }

    bool isNull()    const {return !ptr;}
    bool isNotNull() const {return  ptr;}
};


struct A {
    A() = default;
    A(const A &) = delete;
    A(A &&) = default;
};
struct B : A{};

signed main() {
    A tmp;
    Any x = tmp;
    Any y = A();
    x = std::move(y);
    x.as <A>();
    return 0;
}