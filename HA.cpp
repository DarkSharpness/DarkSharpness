#ifndef _number_high_accuracy_ //�߾��ȿ�
#define _number_high_accuracy_
#include <bits/stdc++.h>

namespace std
{


const unsigned int _mod=-1;

#define uint unsigned int 

vector <uint> _check_num(const vector <uint> &v)//����ǲ�������
{
    if(v.empty()||(*v.cbegin()!=2&&*v.cbegin()!=3))//�ջ���2,3
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

    number (int x)//����ת��
    {v.clear();
        if(x<0) v.push_back(3),x=-x;
        else v.push_back(2);
        v.push_back(x);
    }
    number (long long x)//����ת��
    {
        if(x<0) v.push_back(3),x=-x;
        else v.push_back(2);
        v.push_back(x&_mod);
        x>>=32;
        if(x) v.push_back(x);
    }
    number (int flag,const vector <uint> &x)//����Ϊ��,ż��Ϊ��
    {
        v=x;
        v[0]=2+(flag&1);
        //number(v).print();
    }
    number (const vector <uint> &x)//ֱ�Ӹ�ֵ
    {v=x;}
    

    //�����ж�����

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
        if(v.size()!=m.v.size()) return v.size()<m.v.size();//sizeԽ��,Խ�������
        for(int i=v.size()-1;i!=-1;--i)
            if(v[i]!=m.v[i]) return v[i]<m.v[i];
        return false;//���
    }
    inline bool operator<=(const number &m)const{
        if(v[0]!=m.v[0]) return v[0]>m.v[0];
        if(v.size()!=m.v.size()) return v.size()<m.v.size();
        for(int i=v.size()-1;i!=-1;--i)
            if(v[i]!=m.v[i]) return v[i]<m.v[i];
        return true;//���
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
    
    //λ����

    inline number & operator <<(const number &m)
    {

    }

    //�Ӽ��˳�

    //ȡ��
    inline number operator - (void)const{           
        return number(v[0]^1,v);
    }
    //�ӷ�
    inline number operator + (const number &y)const{ 
    const number &x=*this;
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
            return number(c);
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
            return number(_check_num(c));          //����������
        }
    }
    //����
    inline number operator - (const number &y)const{//����
        return (*this)+number((int(y.v[0])^1),y.v);}
    //�˷�
    inline number operator * (const number &y)const{
        const number &x=*this;
    }
    //���ӷ���
    inline number & operator +=(const number &y){
        (*this)=(*this)+y;
        return *this;
    }
    inline number & operator -=(const number &y){
        (*this)=(*this)-y;
        return *this;
    }
    //��������


    //���
    inline void print()//���
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