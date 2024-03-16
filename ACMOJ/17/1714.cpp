#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long



class term { //项
 public:
    mutable int a;
    int b, c, d;

    term() {}
    // 你可以用 term t(1, 2, 3, 4); 创建一个表示 x^2sin^3xcos^4x 的term
    term(int _a, int _b, int _c, int _d) { 
        a = _a; b = _b; c = _c; d = _d;
    }
    term& operator -(void) {
        a = -a;
        return *this;
    }

    bool operator == (const term &obj) const { // 相等表示是同类项
        return b == obj.b && c == obj.c && d == obj.d;
    }
    bool operator != (const term &obj) const {
        return b != obj.b || c != obj.c || d != obj.d;
    }
    /// @brief 降序排列
    bool operator < (const term &obj) const {
        if(b != obj.b) return b > obj.b;
        if(c != obj.c) return c > obj.c;
        return d > obj.d;
    }
    inline void print() const{
        int aa = abs(a);
        if(aa > 1 || (!b && !c && !d)) {
            printf("%d",aa);
        }
        if(b == 1) {
            putchar('x');
        } else if(b != 0) {
            printf("x^%d",b);
        }
        if(c == 1) {
            printf("sinx");
        } else if(c != 0) {
            printf("sin^%dx",c);
        }
        if(d == 1) {
            printf("cosx");
        } else if(d != 0) {
            printf("cos^%dx",d);
        }
    }
};


class poly { //多项式
 public:
    int n;
    term *t;

    poly() {n = 0; t = NULL;}
    poly(int _n) { // 构造函数
        n = _n;
        t = new term[n];
    }
    poly(const poly &p) {
        n = p.n;
        t = new term[n];
        for (int i = 0; i < n; ++i) {
            t[i] = p.t[i];
        }
    }
    void simplify() { // 合并同类项 
        static set <term> s;
        for(int i = 0 ; i < n ; ++i) {
            if(t[i].a == 0) continue; // Cut leaf
            auto tmp = s.insert(t[i]);
            if(!tmp.second) { // Exist identical element
                tmp.first->a += t[i].a;
                if(tmp.first->a == 0) { // 0 cut leaf
                    s.erase(tmp.first);
                } else {} // Nothing
            } else {} // Nothing
        }
        if(n) delete []t;
        if(s.empty()) { // 0
            n = 1;
            t = new term[n];
            t[0] = term(0,0,0,0);
        } else {
            n = s.size();
            t = new term[n];
            int i = -1;
            for(auto it : s) {t[++i] = it;}
        }
        s.clear();    // post-clear
    }
    poly operator + (const poly &obj) const { // 对 poly 重载加法运算符
        poly ans(n + obj.n);
        for (int i = 0; i < n; ++i) ans.t[i] = t[i];
        for (int i = 0; i < obj.n; ++i) ans.t[i + n] = obj.t[i];
        ans.simplify();
        return ans;
    }
    poly operator - (const poly &obj) const { // 对 poly 重载减法运算符
        poly ans(n + obj.n);
        for (int i = 0; i < n; ++i) ans.t[i] = t[i];
        for (int i = 0; i < obj.n; ++i) {
            ans.t[i + n] = obj.t[i];
            ans.t[i + n].a *= -1;
        }
        ans.simplify();
        return ans;
    }
    poly operator * (const poly &obj) const { // 对 poly 重载乘法运算符
        // 重载后,你可以使用 c = a * b 来进行 poly类型的乘法
        // 为了避免 CE,你不应该对 a 和 b 中的任何数据做出改动
        poly ans(n * obj.n);
        int top = -1;
        for(int i = 0 ; i < n ; ++i) {
            for(int j = 0 ; j < obj.n ; ++j) {
                ans.t[++top] = term(t[i].a * obj.t[j].a,
                                    t[i].b + obj.t[j].b,
                                    t[i].c + obj.t[j].c,
                                    t[i].d + obj.t[j].d);
            }
        }
        ans.simplify();
        return ans;
    }
    poly& operator = (const poly &obj) {
        if (&obj == this) return *this;
        n = obj.n;
        if (t != NULL) delete []t;
        t = new term[n];
        for (int i = 0; i < n; ++i) {
            t[i] = obj.t[i];
        }
        return *this;
    }
    poly derivate() const {  
        poly ans(3 * n);
        int a,b,c,d;
        for(int i = 0 ; i < n ; ++i) {
            a = t[i].a;
            b = t[i].b;
            c = t[i].c;
            d = t[i].d;
            ans.t[3 * i + 0] = term(a * b ,b - 1,c,d);
            ans.t[3 * i + 1] = term(a * c ,b,c - 1,d + 1);    
            ans.t[3 * i + 2] = term(-a * d,b,c + 1,d - 1);
        }
        ans.simplify();
        return ans;
    }
    
    // print out it's information
    void print() const {
        for(int i = 0 ; i < n ; ++i) {
            if(t[i].a < 0) putchar('-');
            else if(i) putchar('+');
            t[i].print();
        }
    }
    // only compare the first element
    bool compare(int num) const{
        if(n != 1) return false;
        if(num == 0) return t[0].a == 0;
        else return t[0].a == num && t[0].b == 0 &&
                    t[0].c == 0   && t[0].d == 0;
    }
    


    ~poly() { // 析构函数,释放内存
        if (t != NULL) delete []t;
    }
};

class frac { //分式
 public:
    poly p, q;

    frac() {}
    frac(int x) {
        p = poly(1);
        p.t[0] = term(x, 0, 0, 0);
        q = poly(1);
        q.t[0] = term(1, 0, 0, 0);
    }
    frac(term _p) {
        p = poly(1);
        p.t[0] = _p;
        q = poly(1);
        q.t[0] = term(1, 0, 0, 0);       
    }
    frac(poly _p, poly _q) : p(_p), q(_q) {}

    frac operator + (const frac &obj) const {
        return frac(p * obj.q + q * obj.p, q * obj.q); // p1/q1+p2/q2=(p1*q2+p2*q1)/(q1*q2)
    }
    frac operator - (const frac &obj) const {
        return frac(p * obj.q - q * obj.p, q * obj.q);
    }
    frac operator * (const frac &obj) const {
        return frac(p * obj.p,q * obj.q);
    }
    frac operator / (const frac &obj) const {
        return frac(p * obj.q,q * obj.p);
    }
    frac derivate() const { // 对分式求导
        return frac(p.derivate() * q - q.derivate() * p,q * q);
    }
    void output() {
        p.simplify();
        q.simplify();
        if(p.compare(0)) {putchar('0');return;}
        if(q.compare(1)) {p.print();return;}
        if(p.n == 1) {p.print();}
        else {putchar('(');p.print();putchar(')');}
        putchar('/');
        if(q.n == 1) {q.print();}
        else {putchar('(');q.print();putchar(')');}
    }
};



inline int read(char *s,int &i) {
    int num = 0;
    while(isdigit(s[i])) {
        num = num * 10 + (s[i] ^'0'); 
        ++i;
    }
    return num;
}

inline term getterm(char *s,int &i) {
    term tmp(0,0,0,0);
    if(isdigit(s[i])) tmp.a = read(s,i);
    else tmp.a = 1;
    if(s[i] == 'x') {
        ++i;
        if(s[i] == '^') tmp.b = read(s,++i);
        else tmp.b = 1;
    }
    if(s[i] == 's') {
        i += 4;
        if(s[i - 1] == '^') tmp.c = read(s,i),++i;
        else tmp.c = 1;
    }
    if(s[i] == 'c') {
        i += 4;
        if(s[i - 1] == '^') tmp.d = read(s,i),++i;
        else tmp.d = 1;
    }
    return tmp;
}
frac getfrac(char *s,int &i) {
    ++i;
    frac tmp = getterm(s,i);
    while(s[i] == '*' || s[i] == '/') {
        if(s[i] == '*') {
            ++i;
            tmp = tmp * getterm(s,i);
            continue;
        } else if(s[i] == '/') {
            ++i;
            tmp = tmp / getterm(s,i);
            continue;
        }
    }
    return tmp;
}


// No brackets case only
void solve(char *s,int n) {
    frac ans(term(0,0,0,0));
    int i = 0;
    frac tmp;
    while(i < n) {
        if(s[i] == '+') {
            ans = ans + getfrac(s,i);
        } else if(s[i] == '-') {
            ans = ans - getfrac(s,i);
        }
    }
    ans.output();
    putchar('\n');
    ans.derivate().output();
}

int main() {
    std::string str;
    std::cin >> str;
    int n = str.length();
    char *s = new char[n + 3]{0};
    for (int i = 1; i <= n; ++i) s[i] = str[i-1];
    s[0] = '+';
    if(s[1] == '-') solve(s+1,n);
    else            solve(s,n+1); 
    delete []s;
    return 0;
}
