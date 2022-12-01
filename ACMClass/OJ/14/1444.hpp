#ifndef EVIL_HPP
#define EVIL_HPP

#include <iostream>
using namespace std;

class Evil{
  private:
    int st, ed, val;
    int *data;
    inline bool check(int tmp) const{return tmp <= ed && st <= tmp;}
    inline int size() const{return ed - st + 1;}
  public:
    Evil(int _st = 0,int _ed = 0,int _val = 0): 
    st(_st),ed(_ed),val(_val) {
        data = new int [size()];
        memset(data,0,size() << 2);
    }
    Evil(const Evil &tmp) : st(tmp.st),ed(tmp.ed),val(tmp.val) {
        data = new int [size()];
        memcpy(data,tmp.data,size() << 2);
    }
    ~Evil() {
        delete []data;
        data = nullptr; // Safe removement
    }
    int &operator [](int index) {
        return check(index) ? data[index - st] : *data;
    }
    int operator [](int index) const{
        return check(index) ? data[index - st] : *data;
    }

    // Copy
    Evil &operator =(const Evil &tmp) {
        if(&tmp == this) return *this;
        *this = Evil(tmp);
        return *this;
    }
    // Move
    Evil &operator =(Evil &&tmp) {
        if(&tmp == this) return *this;
        std::swap(data,tmp.data);
        st   = tmp.st;
        ed   = tmp.ed;
        val  = tmp.val;
        return *this;
    }

    Evil &operator ++(void) {
        ++val;return *this;
    }

    Evil  operator ++(int) {
        Evil tmp(*this);++val;return tmp;
    }

    friend std::ostream &operator <<(std::ostream &os,const Evil &tmp) {
        tmp.Print();
        return os;
    }

    void Print() const{
        cout << val << ' ';
        for(int i = 0;i < ed-st+1;++i)
            cout << data[i] << ' ';
        cout << '\n';
    }
};

#endif//EVIL_HPP    