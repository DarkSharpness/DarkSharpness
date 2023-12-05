#include <vector>
#include <concepts>
#include <iostream>

class Any;

// Concept helper for any type.
template <typename T>
concept non_any = !std::same_as <std::decay_t <T>, Any> && !std::same_as <std::decay_t <T>, std::nullptr_t>;

class Any {
  private:
    /* Base class (abstract class). */
    struct Base {
        virtual ~Base() = default;
        virtual Base *clone() const = 0;
    };


    template <typename T>
    struct Data : Base {
        T data; // Only member

        ~Data() override = default;
        Data(T &&val) : data(std::move(val)) {}
        Data(const T &val) : data(val) {}

        /* Tries to copy an T object and return a T pointer towards the value.
           If attempt failed, nullptr will be returned instead. */
        Base *clone() const noexcept override { return this->try_clone <> (); }

        /* Able to clone, thus return a pointer towards the new T object. */
        template <typename U = T>
        requires std::copy_constructible <U>
        Base *try_clone() const noexcept { return new Data <T> (data); }

        /* Unable to clone, thus return nullptr. */
        template <typename U = T>
        requires (!std::copy_constructible <U>)
        Base *try_clone() const noexcept { return nullptr; }
    };

    Base *ptr;

  public:
    ~Any() { delete ptr; }
    /* Initialize by setting as nullptr. */
    Any() : ptr(nullptr) {}

    /* Special case for nullptr. */
    Any(std::nullptr_t) : ptr(nullptr) {}
    /* Special case for nullptr. */
    Any &operator = (std::nullptr_t) {
        delete ptr;
        ptr = nullptr;
        return *this;
    }

    /* Move the content from rhs by moving pointers. */
    Any(Any &&rhs) noexcept : ptr(rhs.ptr)  { rhs.ptr = nullptr; }
    /* Move the content from rhs by moving pointers. */
    Any &operator = (Any &&rhs) noexcept {
        if(this != &rhs) {
            delete ptr;
            ptr     = rhs.ptr;
            rhs.ptr = nullptr;
        } return *this;
    }

    /* Copy the content from rhs if the inner class of rhs is copy-constructible.
     * Otherwise, this Any object will be set as nullptr.*/
    Any(const Any &rhs) : ptr(rhs.ptr ? rhs.ptr->clone() : nullptr) {}
    /**
     * @brief Copy the content from rhs if the
     * real type of rhs is copy-constructible.
     * Otherwise, this Any object will be set as nullptr.
     */
    Any &operator = (const Any &rhs) noexcept {
        if(this != &rhs) {
            delete ptr;
            ptr = rhs.ptr ? rhs.ptr->clone() : nullptr;
        } return *this;
    }

    /* Perfect forwarding initialization for normal types (Any/nullptr excluded). */
    template <non_any U>
    Any(U &&val) : ptr( new Data <std::decay_t <U>> (std::forward <U> (val)) ) {}
    /* Perfect forwarding assignment for normal types (Any/nullptr excluded). */
    template <non_any U>
    Any &operator = (U &&rhs) {
        using T = std::decay_t <U>;
        ptr = new Data <T> (std::forward <U> (rhs));
        return *this;
    }

    /* Test whether the inner pointer is nullptr. */
    bool is_null() const noexcept {return !ptr;}

    template <typename T>
    friend T *any_cast(Any *) noexcept;

    template <typename T>
    friend T &any_cast(Any &);

    template <typename T>
    friend T any_cast(Any &&);
};

template <typename T>
T *any_cast(Any *tmp) noexcept {
    using U = std::decay_t <T>; // Remove const/volatile/reference
    auto *ptr = dynamic_cast <Any::Data <U> *> (tmp);
    return ptr ? &ptr->data : nullptr;
}

template <typename T>
T &any_cast(Any &tmp) {
    using U = std::decay_t <T>; // Remove const/volatile/reference
    auto *ptr = dynamic_cast <Any::Data <U> *> (tmp.ptr);
    if (!ptr) throw std::bad_cast {};
    return ptr->data;
}

template <typename T>
T any_cast(Any &&tmp) {
    using U = std::decay_t <T>; // Remove const/volatile/reference
    auto *ptr = dynamic_cast <Any::Data <U> *> (tmp.ptr);
    if (!ptr) throw std::bad_cast {};
    return std::move(ptr->data);
}

void func(const int x) {
    std::cout << x << '\n';
}

signed main() {
    int y = 1;
    Any x {y};

    std::string str = "abcd";

    x = y;

    x = std::move(str);
    x = std::vector <int> {1,2,3};

    try {
        any_cast <int> (x);
    } catch(const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    func(any_cast <int> (x = 6));
    return 0;
}
