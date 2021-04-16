#ifndef _number_high_accuracy_ //高精度库 High Accuracy Number based on std::vector
#define _number_high_accuracy_ //Please open it in coding gb2312!
/**
 * @file HA.cpp
 * @author DarkSharpness (darksharpnessxzy@gmail.com)
 * U can contact me through my website <https://DarkSharpness.github.io> .
 * @brief High Accuracy Library
 * @version 1.0
 * @date 2021-04-04
 * @copyright Copyright (C) 2021 DarkSharpness
 * 
 * You can use it to calculate accurate big numbers. 
 * It is based on std::vector and it offers a number printing (base 10) method.
 * So it includes vector , stdlib.h and stdio.h.
 */
#include <vector>
#include <stdio.h>
#include <stdlib.h>

namespace std
{
#define uint unsigned int 


const uint _mod=-1;

// Check if it is a number
vector <uint> _check_num(const vector <uint> &v)
{
    if(v.empty()||(*v.cbegin()!=2&&*v.cbegin()!=3))//空或不是2,3
    {
        printf("%u",*v.cbegin());
        puts("Error!False Number!");
        putchar('1');
        exit(2);
    }
    vector <uint> c=v;
    auto it=c.cend();
    while(*(--it)==0) c.pop_back();
    if(c.size()==1) c[0]=2,c.push_back(0);
    return c;
}

/**
 * @brief A infinite number system based on vector,which involves all operators as the integer.
 * @author DarkSharpness  
 */
class number 
{ 
    /**
     * The first element v[0] is the sign of the number.
     * If v[0] = 2,this number >=0 
     * If v[0] = 3 this number <=0 
     * If else there must be sth. wrong so the program will end
     * v[i] (i>0) is every 4 byte of the number 
     * If the number = 0,the sign can be either 2 or 3,but v[1] should be 0;
     */
    vector <uint> v;
    public:

    //Type changing

    /**
     * @brief change an integer to number
     * @param _x the integer to change to number
     */
    number (int _x)                              
    {v.clear();
        if(_x<0) v.push_back(3),_x=-_x;
        else v.push_back(2);
        v.push_back(_x);
    }

    /**
     * @brief change a long integer to number
     * @param _x the long integer to change to number
     */
    number (long long _x)                        
    {
        if(_x<0) v.push_back(3),_x=-_x;
        else v.push_back(2);
        v.push_back(_x&_mod);
        _x>>=32;
        if(_x) v.push_back(_x);
    }
    
    
    /**
     * @brief       Change a vector to a number with a certain sign.
     * @param _flag If flag mod 2 = 0,this number >= 0.Else it <=0.
     * @param _x    The vector to change to number.(The first element of which is useless.)
     */
    number (int _flag,const vector <uint> &_x)    
    {
        v=_x;
        v[0]=2+(_flag&1);
        //number(v).print();
    }
    
    /**
     * @brief Safe conversion from vector to number.
     * @param _x The vector to change to number. 
     * 
     * If the vector does not conform to the standard of number ,the program will come to an end.
     * If there are extra zeros at the end,they will be cleared to avoid a devastating result.
     */
    number (const vector <uint> &_x)       
    {v=_check_num(_x);}
    
    /**
     * @brief Conversion from vector to number.
     * @param _x    The vector to change to number.
     * @param _flag If it is true , then there is no need to convert safely.Else it should be conver safe.
     * 
     * The sign and extra zeros may not conform to the standard of number if _flag = False.
     * If true,you must make sure that the vector is obeying the rule,or error will occur!
     */
    number (const vector <uint> &_x,bool _flag)   
    {_flag ?v=_x : v=_check_num(_x);}
    
    //Reloading judging operators


    inline bool operator!(void) const{
        if(v.size()==2&&v[1]==0) return true; 
        else return false;
    }
    
    inline bool operator==(const number &_m)const{
        if(v!=_m.v) return true;
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

    //左移
    inline number operator <<(const long long &m)const{
        vector <uint> c;
        c.resize((m>>5)+v.size()+(uint)((*--v.cend())>>(32-(m&31u))),0);
        c[0]=v[0];                      //0符号位   1~m>>5为 0
        if(!(m&31u))                    // 没有余数
        {
            for(int i=v.size()-1;i;--i) c[i+(m>>5)]=v[i];//不用走v[0]
            return number(c);
        } 
        int r=m&31;
        long long x=0; 
        for(int i=1 ; i<v.size() ; ++i)//循环不用v[0]
        {
            x=((long long)v[i]<<r)|(x>>32);
            c[i+(m>>5)]=x&_mod;
        }
       // cout<< (x>>32)  <<endl;
        if(x>>32) c[v.size()+(m>>5)]=x>>32;
        return number(c);
    } 
    //右移
    inline number operator >>(const long long &m)const{
        return *this;
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
    inline number operator - (const number &y)const{
        return (*this)+number(y.v[0]^1,y.v);}
    //乘法
    inline number operator * (const number &y)const{
        const number &x=*this;
        return *this;
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


    /**
     * @brief Default is 0.
     */
    number()
    {
        v.clear();
        v.push_back(2);
        v.push_back(0);
    }
};


}
using namespace std;
//const double c=1ull<<63;

int main()
{
    number x={0,vector <uint>{0,-1u,1u<<30}},y={1,vector <uint>{0,-1u}};
    (x+y).print();
    x.print();
    return 0;
}

#endif