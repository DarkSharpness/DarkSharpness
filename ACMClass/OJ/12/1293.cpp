class shared_ptr {
  private:
    struct node {
        int *ptr;
        unsigned cnt;
        node(int *p,unsigned c):ptr(p),cnt(c){}
        ~node() {
            if(ptr) delete(ptr);
        }
    };
    node *src;

  public:
    int &operator *(void) const{
        return *src->ptr;
    }

    shared_ptr &operator =(const shared_ptr &tmp) {
        if(this == &tmp) return *this;
        if(!--src->cnt) delete this->src;
        src = tmp.src;
        ++src->cnt;
        return *this;
    }

    void reset(int *tmp = 0) {
        if(!--src->cnt) delete this->src;
        src = new node(tmp,1);
    }

    shared_ptr(int *tmp = 0){
        src = new node(tmp,1);
    }

    shared_ptr(const shared_ptr &tmp){
        src = tmp.src;
        ++src->cnt;
    }

    ~shared_ptr() {
        if(!--src->cnt) delete this->src;
    }
};



#include <cassert>
#include <iostream>
using namespace std;

int main() {
    const shared_ptr p(new int(-1));
    cout << *p << endl;
    shared_ptr pp(p);
    cout << *pp << endl;
    *pp = 6;
    cout << *pp << endl;
    cout << *p << endl;
    pp.reset();


    shared_ptr p2;
    p2.reset( new int(4));
    *p2 = 5;
    cout << *p2 << endl;
    p2.reset();

    shared_ptr p3(new int(1));
    int *x = new int(4);
    shared_ptr p4(x);

    int *y = new int(4);
    shared_ptr p5(y);
    shared_ptr p6(p5);
    shared_ptr p7(shared_ptr(shared_ptr(new int(1))));
    shared_ptr p8(new int(4));
    p8 = p8;
    p8 = p7;
    p8 = p6;
    p8 = p5;


    int *z = new int(4);
    shared_ptr p9(z);
    p9 = p9;
    auto p10 = p9;
    p9 = p10;

    int *a = new int(4);
    shared_ptr p11(a);
    shared_ptr p12(p11);
    *p11 += 1;
    cout << *p12 << endl;
    p12.reset(new int(5));
    *p12 += 2;
    cout << *p12 << endl;
}
