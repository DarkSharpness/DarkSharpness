#ifndef _number_high_accuracy_ //�߾��ȿ� High Accuracy Number based on std::vector
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
#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

namespace std
{
#define uint unsigned int 

uint Log2(uint x){
    uint ret;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}

const uint _mod=-1;

// Check if it is a number
vector <uint> _check_num(const vector <uint> &v)
{
    if(v.empty()) return v;
    if((*v.cbegin()!=2&&*v.cbegin()!=3))//�ջ���2,3
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
const char _zero_='0';
const char _nan_='@';
class number 
{ 
    #define Maxsize(_tx) (1<<(Log2(_tx)+1)) //������Ҫ�ռ�

    /**
     * The first element v[0] is the sign of the number.
     * If v[0] = 2,this number >=0 
     * If v[0] = 3 this number <=0 
     * If else there must be sth. wrong so the program will end
     * v[i] (i>0) is every 4 byte of the number 
     * If the number = 0,the sign can be either 2 or 3,but v[1] should be 0;
     * If the vector is empty,it means that something divided by 0 happened.
     */
    vector <uint> v;
    number (const char &c)
    {
        v.clear();
        switch(c)
        {
            case _zero_: 
                v.resize(2,0);
                v[0]=2;
                return;
            case _nan_:
                return;
        }
    }

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
     * @param _sign If sign mod 2 = 0,this number >= 0.Else it <=0.
     * @param _x    The vector to change to number.(The first element of which is useless.)
     */
    number (int _sign,const vector <uint> &_x)    
    {
        v=_x;
        v[0]=2+(_sign&1);
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
    /**
     * @brief Convert string into
     * 
     * @param _str 
     */
    number (const char * &_str)
    {

    }
    
    //�ж������ ok һ������nan,bool����Զ����false;

    inline bool operator!(void) const{
        if(isnan()) return false;
        if(v.size()==2&&v[1]==0) return true; 
        else return false;
    }
    inline bool operator==(const number &_m)const{
        if(isnan()||_m.isnan()) return false;
        if(v==_m.v) return true;
        return false;
    }
    inline bool operator< (const number &_m)const{
        if(isnan()||_m.isnan()) return false;
        if(v[0]!=_m.v[0]) return v[0]>_m.v[0];
        if(v.size()!=_m.v.size()) return v.size()<_m.v.size();//sizeԽ��,Խ�������
        for(int i=v.size()-1;i!=-1;--i)
            if(v[i]!=_m.v[i]) return v[i]<_m.v[i];
        return false;//���
    }
    inline bool operator<=(const number &_m)const{
        if(isnan()||_m.isnan()) return false;
        if(v[0]!=_m.v[0]) return v[0]>_m.v[0];
        if(v.size()!=_m.v.size()) return v.size()<_m.v.size();
        for(int i=v.size()-1;i!=-1;--i)
            if(v[i]!=_m.v[i]) return v[i]<_m.v[i];
        return true;//���
    }
    inline bool operator> (const number &_m)const{
        return !(*this<=_m);
    }
    inline bool operator>=(const number &_m)const{
        return !(*this<_m);
    }
    inline number & operator=(const number &_m){
        v=_m.v;
        return *this;
    }
    
    //λ����

    //�� 

    //���� ok
    inline number operator <<(const long long &m)const{
        if(isnan()||!m||!*this) return *this;
        vector <uint> c;
        uint r=m&31,d=m>>5 ;// m=d*32+r; ( r=[0,32) )
        {
            uint _size=d+v.size()+(uint)((*--v.cend()>=(1<<(32-r))));
            c.reserve(Maxsize(_size));
            c.resize(_size);
            c[0]=v[0];                      //0����λ   1~m>>5Ϊ 0
        }
        if(!r)                    // û������
        {
            for(int i=v.size()-1;i;--i) c[i+d]=v[i];//������v[0]
            return number(c,true);
        } 
        unsigned long long x=0; 
        for(int i=1 ; i<v.size() ; ++i)//ѭ������v[0]
        {
            x=((long long)v[i]<<r)|(x>>32);
            c[i+d]=x&_mod;
        }
        if(x>>32) c[v.size()+d]=x>>32;
        return number(c,true);//���ж����0
    } 
    //����
    inline number operator >>(const long long &m)const{
        if(isnan()||!m||!*this) return *this;   
        vector <uint> c;   
        const uint r=m&31,d=m>>5 ;// m=d*32+r; ( r=[0,32) )
        {   
            const uint _space=d+((*--v.cend())<(1<<r));
            if(v.size()<=_space+1) return number(_zero_);
            c.reserve(Maxsize(v.size()-_space));    //����ռ�
            c.resize(v.size()-_space);
        
        }
        c[0]=v[0];//���Ų���
        if(!r) 
        {   
            for(int i=v.size()-1 ; i>=1+d ; --i) c[i-d]=v[i];
            return number(c,true);
        }
        unsigned long long x=v[1+d];x<<=(32-r);
        for(uint i=1 ; i+d+1<v.size() ; ++i)
        {
            x=(x>>32)|((unsigned long long)v[i+d+1]<<(32-r));
            c[i]=x;
        }
        if(x>>32) *--c.end()=x>>32;
        return number(c,true);
    }



    //�Ӽ��˳�

    //ȡ�� ok
    inline number operator - (void)const{  
        if(isnan()) return *this;        
        else return number(v[0]^1,v);
    }
    //�ӷ� ok
    inline number operator + (const number &y)const{ 
        const number &x=*this;
        if(v.empty()) return x;if(y.v.empty())return y; //����
        if(!x) return y;if(!y) return x;                //0
        if(x.v[0]==y.v[0])                       //ͬ�żӷ�
        {
            vector <uint> c;
            c.push_back(x.v[0]);                //c[0]=ԭ����
            const number *a=(&x),*b=(&y);
            if( (1,a->v)<(1,b->v) ) swap(a,b);  //��֤a����ѭ��
            unsigned long long t=0;             //��λ
                                                //��һλ�Ƿ���λ,������++
            for(auto itx=++a->v.cbegin(),ity=++b->v.cbegin() ; itx!=a->v.cend() ;++itx)
            {
                if(ity!=b->v.cend()){t+=*ity;++ity;}//���ײ��Ͳ�����
                t+=*itx;
                c.push_back(t&_mod);
                t>>=32;
            }
            if(t) c.push_back(t);               //���һλ���Ƿ�Ҫ��
            return number(c,1); //����Ҫ���
        }

        else                                 //һ��һ���ӷ�������
        {                                   //��ʱy�Ǹ��Ż���,Ĭ�ϸ���
            vector <uint> c;
            c.push_back(x.v[0]);            //Ĭ��(abs(x)>abs(y))
            const number *a=(&x),*b=(&y);
            if( number(1,a->v)<number(1,b->v) ) swap(a,b),c[0]=c[0]^1; //��x�ż���
            long long t=0;                    //��λ
                                     //��ʱ abs(*a)>abs(*b) ��0λ�Ƿ���λ,����++
            for(auto itx=++a->v.cbegin(),ity=++b->v.cbegin() ; itx!=a->v.cend() ;++itx)
            {
                if(ity!=b->v.cend()){t+=*ity;++ity;}//���ײ��Ͳ�����   
                t-=*itx;
                c.push_back(-t);                   //���t<=0 �������.�������0 ��ô���ý�����������һλ
                if(t<=0) t=0;
                else t=1;
            }
            return number(c);          //����������
        }
    
    }
    //inline ���� ok
    inline number operator - (const number &y)const{
        return (*this)+number(y.v[0]^1,y.v);}
    //�˷�
    inline number operator * (const number &y)const{
        const number &x=*this;
        if(isnan()) return x;if(y.isnan()) return y;
        if(!x||!y) return _zero_;
        
        return *this;
    }
    
    
    //���ӷ��� 
    /*
    inline number & operator +=(const number &y){
        (*this)=(*this)+y;
        return *this;
    }
    inline number & operator -=(const number &y){
        (*this)=(*this)-y;
        return *this;
    }
    */ 


   //��������

    //�ж��Ƿ���һ������
    inline bool isnan()const{
        if(v.empty()) return true;
        else return false;
    }

    //��� �����ڵ���,�Ժ�ɾ
    inline void print()const{
        if(v.empty()) {puts("Not a Number!");return;}
        if(v.size()==1) {puts("0");return;}
        if((*v.cbegin()-2u)>1u){puts("Wrong format!");return;}
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
    //#undef Maxsize(_tx)
};
const number NaN={vector <uint>{},true};


}
using namespace std;
//const double c=1ull<<63;

int main()
{
    number x={0,vector <uint>{0,0,0,1u<<30}},y=number{1,vector <uint>{0,123,1u<<30,323}};
    number z={0,vector <uint>{0,0,1u<<30}};
    //(x<<130).print();
    //y.print();
    x.print();
    (x>>62).print();
    (y>>62).print();
    (z>>62).print();
    return 0;
}

#endif