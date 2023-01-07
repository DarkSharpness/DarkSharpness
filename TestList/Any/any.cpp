#include <iostream>
#include <Dark/memory> // This is used to test memleak and storage info.
#include <vector>

/**
 * @brief A dynamic class which can hold any type (nullptr_t excluded)
 * and support basic coversion function.
 * 
 */
class Any {
  private:
    /* Base class (abstract class). */
    struct Base {
        virtual ~Base() = default;
        virtual Base *clone() const = 0;
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
    Any(U &&val) : ptr( new Data <std::decay_t <U>> (std::forward <U> (val)) ) {}


    Any(Any &&rhs) : ptr(rhs.ptr) { rhs.ptr = nullptr; }
    Any(const Any &rhs) : ptr(rhs.ptr->clone()) {}

    /* Special case for null_pointer. */
    Any &operator = (std::nullptr_t) {
        this->~Any();
        ptr = nullptr;
        return *this;
    }

    /**
     * @brief Move the content from rhs by simply swaping pointers.
     * 
     * @param rhs   The content source to move from.
     * @return Any& This object , which is equivently to previous rhs.
     */
    Any &operator = (Any &&rhs) noexcept {
        if(this != &rhs) {
            this->~Any();
            ptr     = rhs.ptr;
            rhs.ptr = nullptr;
        }
        return *this;
    }

    /**
     * @brief Copy the content from rhs if the inner class
     * of rhs is copy-constructible.
     * Otherwise , this Any object will be set as nullptr.
     * 
     * @param  rhs  The content source to copy from.
     */
    Any &operator = (const Any &rhs) noexcept {
        if(this != &rhs) {
            this->~Any();
            if(rhs.ptr) ptr = rhs.ptr->clone();
            else        ptr = nullptr;
        }
        return *this;
    }

    /* Copy rhs's content. */
    Any &operator = (Any &rhs) { return *this = (const Any &)rhs; }
    /* Copy rhs's content. */
    Any &operator = (const Any &&rhs) { return *this = rhs; }

    /* Perfect forwarding for normal types. */
    template <class U>
    Any &operator = (U &&rhs) {
        using T = std::decay_t <U>;
        Data <T> *tmp = dynamic_cast <Data <T> *> (ptr);
        if(!tmp) {
            this->~Any();
            ptr = new Data <std::decay_t <U>> (std::forward <U> (rhs));
        } else {
            tmp->data = std::forward <U> (rhs);
        }
        return *this;
    }

    template <class U>
    Any &operator = (const U &&rhs) {
        using T = std::decay_t <U>;
        Data <T> *tmp = dynamic_cast <Data <T> *> (ptr);
        if(!tmp) {
            this->~Any();
            ptr = new Data <std::decay_t <U>> (std::forward <U> (rhs));
        } else {
            tmp->data = std::forward <U> (rhs);
        }
        return *this;
    }

    template <typename U>
    operator U() { return as <U> (); }

    template <typename U>
    operator const U() const { return as <const U> (); }

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


void func(const int &x) {
    std::printf("space:%d\n",x);
}


signed main() {
    Any x(1);
    std::string str = "abcd";
    x = std::move(str);
    x = std::vector <int> {1,2,3};
    func(x = 0);
    return 0;
}
