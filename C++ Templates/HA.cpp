#ifndef _number_high_accuracy_ //高精度库
#define _number_high_accuracy_
#include <bits/stdc++.h>

namespace std
{


const unsigned int _mod=-1;

#define uint unsigned int 

vector <uint> _check_num(const vector <uint> &v)//检查是不是数字
{
    if(v.empty()||(*v.cbegin()!=2&&*v.cbegin()!=3))//空或不是2,3
    {
        printf("%u",*v.cbegin());
        puts("Error!False Number!");
        exit(2);
    }
    vector <uint> c=v;
    auto it=c.cend();
    while(*(--it)==0) c.pop_back();
    return c;
}


class number 
{ 
    vector <uint> v;// v[0]=2 >=0 , v[0]=3 <0;
   
    public:
    inline void init()
    {   
        v.clear();
        v.push_back(2);
    }

    number (int x)//类型转换
    {v.clear();
        if(x<0) v.push_back(3),x=-x;
        else v.push_back(2);
        v.push_back(x);
    }
    number (long long x)//类型转换
    {
        if(x<0) v.push_back(3),x=-x;
        else v.push_back(2);
        v.push_back(x&_mod);
        x>>=32;
        if(x) v.push_back(x);
    }
    number (int flag,const vector <uint> &x)//奇数为负,偶数为正
    {
        v=x;
        v[0]=2+(flag&1);
        //number(v).print();
    }
    number (const vector <uint> &x)//直接赋值
    {v=x;}
    

    //符号判断重载

    inline bool operator!(void) const{
        if(v.size()==2&&v[1]==0) return true; 
        else return false;
    }
    inline bool operator==(const number &m)const{
        if(v<m.v) return true;
        return false;
    }
    inline bool operator< (const number &m)const{
        if(v[0]!=m.v[0]) return v[0]>m.v[0];
        if(v.size()!=m.v.size()) return v.size()<m.v.size();//size越大,越会出问题
        for(int i=v.size()-1;i!=-1;--i)
            if(v[i]!=m.v[i]) return v[i]<m.v[i];
        return false;//相等
    }
    inline bool operator<=(const number &m)const{
        if(v[0]!=m.v[0]) return v[0]>m.v[0];
        if(v.size()!=m.v.size()) return v.size()<m.v.size();
        for(int i=v.size()-1;i!=-1;--i)
            if(v[i]!=m.v[i]) return v[i]<m.v[i];
        return true;//相等
    }
    inline bool operator> (const number &m)const{
        return !(*this<=m);
    }
    inline bool operator>=(const number &m)const{
        return !(*this<m);
    }
    inline number & operator=(const number &m){
        v=m.v;
        return *this;
    }
    
    //位运算

    inline number & operator <<(const number &m)
    {

    }

    //加减乘除

    //取负
    inline number operator - (void)const{           
        return number(v[0]^1,v);
    }
    //加法
    inline number operator + (const number &y)const{ 
    const number &x=*this;
        if(x.v[0]==y.v[0])                       //同号加法
        {
            vector <uint> c;
            c.push_back(x.v[0]);                //c[0]=原符号
            const number *a=(&x),*b=(&y);
            if( (1,a->v)<(1,b->v) ) swap(a,b);  //保证a会后出循环
            unsigned long long t=0;             //进位
                                                //第一位是符号位,所以是++
            for(auto itx=++a->v.cbegin(),ity=++b->v.cbegin() ; itx!=a->v.cend() ;++itx)
            {
                if(ity!=b->v.cend()){t+=*ity;++ity;}//到底部就不做了
                t+=*itx;
                c.push_back(t&_mod);
                t>>=32;
            }
            if(t) c.push_back(t);               //最后一位看是否要进
            return number(c);
        }


        else                                 //一正一负加法当减法
        {                                   //此时y是负号化了,默认负号
            vector <uint> c;
            c.push_back(x.v[0]);            //默认(abs(x)>abs(y))
            const number *a=(&x),*b=(&y);
            if( number(1,a->v)<number(1,b->v) ) swap(a,b),c[0]=c[0]^1; //反x号即可
            long long t=0;                    //借位
                                     //此时 abs(*a)>abs(*b) 第0位是符号位,所以++
            for(auto itx=++a->v.cbegin(),ity=++b->v.cbegin() ; itx!=a->v.cend() ;++itx)
            {
                if(ity!=b->v.cend()){t+=*ity;++ity;}//到底部就不做了   
                t-=*itx;
                c.push_back(-t);                   //如果t<=0 借用清空.如果大于0 那么还得借用来补满这一位
                if(t<=0) t=0;
                else t=1;
            }
            return number(_check_num(c));          //减法必须检查
        }
    }
    //减法
    inline number operator - (const number &y)const{//减法
        return (*this)+number((int(y.v[0])^1),y.v);}
    //乘法
    inline number operator * (const number &y)const{
        const number &x=*this;
    }
    //复杂符号
    inline number & operator +=(const number &y){
        (*this)=(*this)+y;
        return *this;
    }
    inline number & operator -=(const number &y){
        (*this)=(*this)-y;
        return *this;
    }
    //其他功能


    //输出
    inline void print()//输出
    {
        if(v.size()==1) 
        {puts("0");return;}
        if(*v.cbegin()==3) putchar('-');
        for(auto i=++v.cbegin() ; i!=v.cend() ; ++i)
            printf("%u ",*i);
        puts("");    
    }

};


}
using namespace std;

int main()
{

    number x={0,vector <uint>{0,-1u,4u}},y={1,vector <uint>{0,-1u}};
    (x-y).print();
    (-x+y).print();
    return 0;
}

#endif