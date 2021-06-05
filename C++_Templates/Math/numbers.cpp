//#pragma GCC optimize(3)
#include <vector>
#include <iostream>
#include <string.h>
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
//const uint maxn=2147483647;

namespace std
{
    //快速Log2函数
    #ifndef _Dark_Math_H_
    inline uint Log2(const uint &x)
    {
        uint ret;
        __asm__ __volatile__("bsrl %1, %%eax"
                             : "=a"(ret)
                             : "m"(x));
        return ret;
    }
    #endif
    #define maxsize(_tx_) (1 << (Log2(_tx_) + 1))
    #define bk break;
    #define y (*this)
    #define checknan() (isnan() || _N.isnan())
        
    //检查数组 --已经通过测试
    inline const vector<uint> checkv(const vector<uint> &c)
    {
        if (c.size() <= 1 || *--c.cend() != 0)
            return c;
        auto it = c.cend();
        auto siz = c.size();
        while ((--it) != c.cbegin() && (*it) == 0)
            --siz; //如果最后一个是begin也不处理了
        vector<uint> t;
        t.reserve(maxsize(siz));
        for (auto i = c.cbegin(); i != it; ++i)
            t.push_back(*i);
        t.push_back(*it);
        return t;
    }

    class number
    {
    private:
        vector <uint> v;//数字数组

        bool sign;      //符号
        
        //指令处理
        number(const char &c, const uint &x)
        {
            switch (c)
            {
                case '#':
                    v.clear();
                    v.reserve(x);
                    bk;
                default:
                    puts("Error!");
                    exit(1u);
            }
        }
        //等同v.size()
        inline uint size() const{
            return v.size();
        }
        //等同v[x]
        inline uint operator[](const uint &x) const{
            return v[x];
        }
        //等同v.pushback(x)
        inline void push_back(const uint &x){
            v.push_back(x);
        }
        /*对一个新的number预分配内存 x为所需内存下限
            inline void reassign(const uint &x)
            {
                if(v.capacity()>(x<<1))//太多
                    v.resize(maxsize(x)),v.shrink_to_fit();
                else if(v.capacity()>=x) return;//no need to shrink
                else v.reserve(maxsize(x));     //not enough
            }
            */

    public:
        //类型转化

        explicit number()
        {
            sign = false;
            v.clear();
            v.shrink_to_fit();
            v.push_back(0);
        }
        explicit number(int x)
        {
            v.clear();
            v.swap(v);
            x < 0 ? sign = true, x = -x : sign = false;
            v.reserve(2);
            v.push_back(x);
        }
        explicit number(long long x)
        {
            v.clear();
            v.swap(v);
            x < 0 ? sign = true, x = -x : sign = false;
            v.reserve(x>>32? 4 : 2);
            v.push_back(uint(x));
            if (x >> 32)
                v.push_back(x >> 32);
        }
        explicit number(const bool &flag, const vector<uint> &c)
        {
            v.clear();
            v.swap(v);
            sign = flag;
            //v.reserve(maxsize(c.size()));
            //cout<< v.capacity()<<endl;
            v = checkv(c);
            //cout<< v.capacity()<<endl;
        }
        explicit number(const char *&c) //最后一个是空格
        {
            v.clear();
            uint i;
            for (i = 0; c[i] ; ++i) //如果有错 就gg
                if (!isdigit(c[i]))
                {
                    puts("Error");
                    return;
                }
            number b(1);

            for (   ; i--; b = b * number(10))
            {
                if (c[i] == '0')
                    continue;
                y = y + b * number(c[i] - '0');
            }
        }
        inline operator bool()const{
            if(v.empty()) return false;                //NaN
            if(v.size()==1&&v.front()==0) return false;//0
            else return true;                          //非0
        }
        inline operator int()const{
            if(v.empty()) return 0;
            int x=v.front()&2147483647;
            return sign ? -x : x;
        }
        inline operator long long()const{
            if(v.empty()) return 0;
            else if(v.size()==1) 
            {
                int x=v.front()&((1<<31)-1);
                 return sign ? -x : x;
            }
            long long x=v.front();
            cout << x <<endl;
            x+=(((long long)(v[1]&2147483647))<<32);
            return sign ? -x: x;
        }
        //逻辑运算符,涉及nan永远false

        inline bool operator!(void) const
        {
            //if(isnan()) return false;
            if (v.size() == 1 && *v.cbegin() == 0)
                return true;
            else
                return false;
        }
        inline bool operator>(const number &_N) const
        {
            if (checknan())
                return false;
            if (sign != _N.sign)
                return sign < _N.sign;
            if (size() != _N.size())
                return sign ? size() < _N.size() : size() > _N.size();
            for (uint i = size(); i--;)
                if (v[i] != _N[i])
                    return sign ? v[i] < _N[i] : v[i] > _N[i];
            return false;
        }
        inline bool operator>=(const number &_N) const
        {
            if (checknan())
                return false;
            if (sign != _N.sign)
                return sign < _N.sign;
            if (size() != _N.size())
                return sign ? size() < _N.size() : size() > _N.size();
            for (uint i = size(); i--;)
                if (v[i] != _N[i])
                    return sign ? v[i] < _N[i] : v[i] > _N[i];
            return true;
        }
        inline bool operator<(const number &_N) const
        {
            if (checknan())
                return false;
            if (sign != _N.sign)
                return sign > _N.sign;
            if (size() != _N.size())
                return sign ? size() > _N.size() : size() < _N.size();
            for (uint i = size(); i--;)
                if (v[i] != _N[i])
                    return sign ? v[i] > _N[i] : v[i] < _N[i];
            return false;
        }
        inline bool operator<=(const number &_N) const
        {
            if (checknan())
                return false;
            if (sign != _N.sign)
                return sign > _N.sign;
            if (size() != _N.size())
                return sign ? size() > _N.size() : size() < _N.size();
            for (uint i = size(); i--;)
                if (v[i] != _N[i])
                    return sign ? v[i] < _N[i] : v[i] > _N[i];
            return true;
        }
        inline bool operator==(const number &_N) const
        {
            if (checknan())
                return false;
            if (sign == _N.sign && v == _N.v)
                return true;
            else
                return false;
        }
        inline bool operator!=(const number &_N) const
        {
            if (checknan())
                return false;
            if (sign != _N.sign || v != _N.v)
                return false;
            else
                return true;
        }
        /**
         * @brief Equivlent in number.
         * @param _N The number that is equaled to. 
         * @return Number _N.
         * Note that if the original space is larger than required,it will not shrink.
         * It is the user's duty to manage the space by using shrink()
         */
        inline number operator=(const number &_N)
        {
            if (_N.isnan())
                return _N;
            sign = _N.sign;
            v = _N.v;
            return y;
        }

        //位运算符 

        inline number operator~(void)const{
            number c('#',size());
            for(auto i:v)
            {
                
            }
        }
        inline number operator<<(const ll &x) const
        {
            if (isnan()||!y||!x)return y;
            if (x < 0)  return y >> (-x);
            const uint m = x >> 5, r = x & 31, siz =(m+v.size()+(v.back()>>(32 - r)>0));
            number c ('#',siz);
            c.sign = sign;
            c.v.resize(m, 0);
            if (!r)
            {
                for (uint i : v)
                    c.v.push_back(i);
            }
            else
            {
                ull t = 0;
                for (uint i : v)
                {
                    t = (t >> 32) + (((ull)i) << r);
                    c.v.push_back(uint(t));
                }
                if (t >> 32)
                    c.v.push_back(t >> 32);
            }
            return c;
        }/*
        inline number operator<<=(const ll &x)
        {
            if (isnan() || !y || !x)//自己不变
                return y;
            if (x < 0)
                return (y >>= (-x));
            const uint m = x >> 5, r = x & 31;
            const uint c=v.back()>>(32-r),
            siz = (m + v.size() + (c>0));
            v.reserve(siz>v.capacity() ? maxsize(siz) : siz);
            v.resize(siz);
            if(c>0) v.back()=c;
            if(!r){}
            else{
                for(uint i=v.size()-1-(c>0); i>v.size()-m ;--i)
                {
                    v[i]=
                }
            }
        }*/
        inline number operator>>(const ll &x) const
        {
            if (isnan() || !y || !x)
                return y;
            if (x < 0)
                return y << (-x);
            const uint m = x >> 5, r = x & 31;
            const int siz = (v.size() - m - ((*--v.cend()) < (1 << r)));
            //cout << siz <<" "<< maxsize(siz) <<endl;
            if (siz <= 0)
                return number(0);
            number c('#',siz);
            c.sign = sign;
            if (!r)
            {
                for (uint i = m; i < v.size(); ++i)
                    c.v.push_back(v[i]);
            }
            else
            { //前m位没了
                ull t = v[m];
                t <<= (32 - r);
                for (uint i = m + 1; i < v.size(); ++i)
                {
                    t = (t >> 32) + (v[i] << (32 - r));
                    c.v.push_back(uint(t));
                }
                if (t >> 32)
                    c.v.push_back(t >> 32);
            }
            //cout<< c.v.capacity() <<endl;
            return c;
        }
        
        //  +-*/%运算符

        inline number operator-(void) const
        {
            number c = y;
            c.sign = !sign;
            return c;
        }
        inline number operator+(const number &x)
        {
            //鉴定0 非数
            {if (x.isnan())
                return x;
            if (y.isnan())
                return y;
            if (!x)
                return y;
            if (!y)
                return x;}
            
            if (x.sign == y.sign) //加法
            {
                const number *a = &x, *b = &y;
                if (x.size() > y.size())
                    swap(a, b); //a是小的
                number c('#', b->size() + 1);
                c.sign = sign;
                ull t = 0;
                uint i = 0;
                while (i != a->size())
                    c.push_back(t = (t >> 32) + (*a)[i] + (*b)[i++]);
                while (t >> 32 && i != b->size())
                    c.push_back(t = (t >> 32) + (*b)[i++]);
                while (i != b->size())
                    c.push_back((*b)[i++]);
                if (t >> 32)
                    c.push_back(t >> 32);
                return c;
            }
            else //减法
            {
                const number *a, *b; //a比b短, b>a 所以是b-a
                switch (abscmp(x))   //  y>x:1  y<x:0  x=y:-1
                {
                case 0:
                    a = &y, b = &x;
                    bk;
                case 1:
                    a = &x, b = &y;
                    bk;
                case -1:
                    return number(0);
                    bk;
                }
                number c('#', b->size());
                c.sign = b->sign;
                c.print();
                long long t = 0; //借位
                uint i = 0;
                while (i != a->size())
                {
                    t = t + (*a)[i] - (*b)[i++];
                    c.push_back(-t);
                    if (t > 0)
                        t = 1;
                    else
                        t = 0;
                }
                //cout << i << endl;
                if (t)
                { //先把0的项处理了 然后再处理最后一个
                    while (!(*b)[i])
                        c.push_back(-1u), ++i;
                    c.push_back((*b)[i++] - 1);
                }
                while (i != b->size())
                    c.push_back((*b)[i++]);
                i = c.size();
                while (c[--i] == 0)
                    c.v.pop_back();
                //c.print();
                return c;
            }
        }
        inline number operator-(number x)
        {
            return (*this) + (-x);
        }
        inline number operator*(const number &x) const
        {
            //鉴定0和非数
            {if (x.isnan())return x;if (y.isnan())return y;
            if (!x)return x; if (!y)return y;}
            
            const number *a, *b; // b 比 a 长
            x.size() > y.size() ? a = &y, b = &x : a = &x, b = &y;
            number c('#', b->size() + a->size()), g=number('#', b->size() + 1);
            c.push_back(0);
            c.sign = x.sign ^ y.sign;
            g.sign = c.sign;
            for (ull it = 0; it < a->size();)
            {
                ull t = 0;
                for (ull it2 : b->v)
                {
                    t = (t >> 32) + it2 * a->v[it]; //取t前32位
                    g.push_back(uint(t));
                }
                if (t >> 32)
                    g.push_back(t>>32);
                c = c + g;
                g.v.assign(++it, 0);
            }
            return c;
        }
        inline number operator/(const uint &x)const{

        }
        inline number operator/(const number &x) const
        {
            if (x.isnan()) return x;
            if (y.isnan()) return y;
            if (!x)        return number('#', 0);
            if (!y)        return y;
        }
        //奇怪的函数

        //比较大小 如果大于则返回1 小于返回0 等于返回-1
        inline char abscmp(const number &x) const
        {
            if (size() != x.size())
                return size() > x.size();
            for (uint i = size(); i--;)
                if (v[i] != x[i])
                    return v[i] > x[i];
            return -1;
        }
        //比较前or后t位的大小与x的净值(fl=true 前部(最底部) fl=false 后部(最高位))
        inline char abscmp(const number &x,const size_t &t,const bool &fl) const{
            if(t>v.size()) exit(2u);
            if(fl==true)
            {

            }
        }

        //十进制输出
        inline const char *c_str()const{
            if (isnan())  return "Not a Number!";
            number t(1);
            t.v.reserve(size() + 1);
            uint siz=0;
            while(abscmp(t)==1) t=t*number(10),siz++;
            t=number(1);
            char *c=(char *)malloc(siz+1);
            for(uint i=0 ; i<siz ; ++i)//siz位
                ;
            return c;                
        }   
        //测试输出
        inline void print() const
        {
            printf("vector:");
            if (isnan())
                printf("Not a number! ");
            else if (!y)
                printf("0 ");
            else
            {
                if (sign)
                    putchar('-');
                for (uint it : v)
                    printf("%u ", it);
            }
            printf("size:%u capacity:%u\n", v.size(), v.capacity());
        }
        //判断是否存在
        inline bool isnan() const
        {
            return v.empty() ? true : false;
        }
        //等价于shrink to fit,用于节约空间
        inline void shrink()
        {
            v.shrink_to_fit();
        }
        //访问第某位
        inline bool bit(const ull &_x)const{
            if(_x>>5 >= v.size()) return false;//nan也是返回0 超出也是返回0
            return v[_x>>5]&(1u<<(_x&31));
        }
        //清空内存占用,变成0而不是NaN
        inline void empty()
        {
            v.clear();
            v.shrink_to_fit();
            v.push_back(0);
        }
        //清空vector ,变成0而不是NaN
        inline void clear()
        {
            v.clear();
            v.push_back(0);
        }
        
    };
    const number number_zero(0);
    const number NaN(number_zero/number(0));
#undef checknan
#undef y
#undef maxsize
}

using namespace std;

int main()
{

    number c(0, vector<uint>{20,-1u,1}), z(0, vector<uint>{1,1});
    //c.print();
    //cout << c.c_str();
    cout << (long long)c <<endl;
    //cout << 'c' <<endl;
    return 0;
}