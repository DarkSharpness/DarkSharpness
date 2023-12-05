#include <iostream>

struct Base {
    Base() = default;
    void A()            { std::puts("Base::A()"); }
    virtual void B()    { std::puts("Base::B()"); }
    virtual void C() const { std::puts("Base::C()"); }
    virtual ~Base()     { std::puts("~Base()"); }
};

struct Derived1 : Base {
    Derived1() = default;
    virtual void A()    { std::puts("Derived1::A()"); }
    void B()            { std::puts("Derived1::B()"); }
    virtual void C()    { std::puts("Derived1::C()"); }
    virtual ~Derived1() { std::puts("~Derived1()"); }
};

struct Derived2 : Base {
    Derived2() = default;
    virtual void A()    { std::puts("Derived2::A()"); }
    void B() override   { std::puts("Derived2::B()"); }
    void C() const      { std::puts("Derived2::C()"); }
    virtual ~Derived2() { std::puts("~Derived2()"); }
};

struct Derived3 : Base {
    Derived3() = default;
    virtual void A()    { std::puts("Derived3::A()"); }
    void B()            { std::puts("Derived3::B()"); }
    void C()            { std::puts("Derived3::C()"); }
    virtual ~Derived3() { std::puts("~Derived3()"); }
};

struct Derived4 : Derived1 {
    Derived4() = default;
    void A()            { std::puts("Derived4::A()"); }
    void B()            { std::puts("Derived4::B()"); }
    void C() override   { std::puts("Derived4::C()"); }
    virtual ~Derived4() { std::puts("~Derived4()"); }
};

void test1(Base p) {
    p.A();
    p.B();
    p.C();
}

void test2(Base &p) {
    p.A();
    p.B();
    p.C();
}

void print_line(); // 输出分割 ----------------------------

signed main() {
    Base *ptr = new Derived3;

    test1(*ptr);
    print_line();

    test2(*ptr);
    print_line();

    delete ptr;
    return 0;
}


void print_line() {
    std::puts(std::string(20, '-').c_str());
}
