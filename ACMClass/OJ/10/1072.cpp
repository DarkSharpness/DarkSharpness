#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
long long sqr(long long tmp) {return tmp * tmp;}
class CircleSet {
    friend istream &operator>>(istream &in, CircleSet &obj);  
  private:
    struct Circle {
        long long x, y, r;
        Circle(long long _x = 0, long long _y = 0, long long _r = 0): 
            x(_x), y(_y), r(_r) {}            
        friend long long dist(const Circle &X,const Circle &Y) {
            return sqr(X.x - Y.x) + sqr(X.y - Y.y); 
        }
    };
    int count;//集合中圆的数目
    Circle *circles;//集合中所有圆
  public:
    CircleSet(int n): count(n) {
        circles = new Circle[n];
    }
    ~CircleSet() {delete []circles;}
    long long operator [](int __n) const {return circles[__n].r;}
    bool checkContaining(int p, int q) const{
        if(p == q) return false;
        const Circle &X = circles[p];
        const Circle &Y = circles[q];
        if(X.r < Y.r) return false;
        return dist(X,Y) < sqr(X.r - Y.r);
    }
    int getCircleContainingQ(int q) const{
        long long r = 9223372036854775807;
        for(int i = 0 ; i < count ; ++i) 
            if(checkContaining(i,q) && circles[i].r < r)
                r = circles[i].r;
        return r;
    }

};

istream &operator>>(istream &in, CircleSet &obj) {
    for (int i = 0; i < obj.count; ++i) {
        in >> obj.circles[i].x >> obj.circles[i].y >> obj.circles[i].r;
    }
    return in;
}


int main() {
    int n, m;
    cin >> n >> m;
    CircleSet set(n);
    cin >> set; //输入集合中的所有圆
    while (m--) {
        int type, p, q;
        cin >> type;
        if (type == 1) {
            //do nothing 
        } else if (type == 2) {
            for (int i = 0; i < n; ++i) {
                cout << set[i] << ' ';
            }
            cout << endl;
        } else if (type == 3) {
            cin >> p >> q;
            cout << set.checkContaining(p, q) << endl;
        } else if (type == 4) {
            cin >> q;
            cout << set.getCircleContainingQ(q) << endl;
        }
    }
    return 0;
}