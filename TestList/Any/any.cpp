#include <iostream>

class Any {
    struct Base { 
        virtual Base* clone() = 0; 
        virtual ~Base() = default;
    };

    template<typename T>
    struct Data : Base {
        T data;
        Data(const T& val) : data( val ) {}
        virtual Base* clone() override { return new Data <T> (data); }
        virtual ~Data() = default;
    };

    Base* ptr;

  public:
    Any() : ptr(nullptr) {}
    template<typename T>
    Any(const T& t) : ptr( new Data<T>(t) ) {};
    Any(const Any& rhs) { ptr = rhs.ptr->clone(); }
    Any(Any &&rhs) { ptr = rhs.ptr; rhs.ptr = nullptr; }

    Any& operator=(const Any& rhs) {
        if(this != &rhs) {
            if (ptr) delete ptr;
            ptr = rhs.ptr->clone();
        }
        return *this;
    }

    Any &operator=(Any&& rhs) {
        if (ptr) delete ptr;
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
        return *this;
    }

    template <typename T>
    bool is() const {
        const Data <T> *tmp = dynamic_cast <const Data <T> *> (ptr);
        return tmp;
    }

    template <typename T>
    T& as() {
        Data <T> *tmp = dynamic_cast <Data <T> *> (ptr);
        if(!tmp) throw "bad cast";
        return tmp->data;
    }

    bool isNull() const {return !ptr;}
    bool isNotNull() const {return ptr;}

    ~Any(){ delete ptr; }
};

struct A {};
struct B : A{};

signed main() {
    Any x(1);
    x = A();
    try {
        x.as <B> ();
    } catch(const char *ptr) {
        std::cout << ptr;
    }
    return 0;
}