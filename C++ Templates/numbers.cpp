#include<bits/stdc++.h>
typedef unsigned int uint ;
namespace std{
    //快速Log2函数
    uint Log2(uint x){
    uint ret;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
    }
    #define maxsize(_tx_) (1<<(Log2(_tx_)+1))
    
    //检查数组 --已经通过测试
    vector <uint> checkv(const vector <uint> &c)
    {
        if(c.size()<=1||*--c.cend()!=0) return c;
        auto it=c.cend();
        auto siz=c.size();
        while((--it)!=c.cbegin()&&(*it)==0)--siz; //如果最后一个是begin也不处理了
        vector <uint> t;
        t.reserve(maxsize(siz));
        for(auto i=c.cbegin();i!=it;++i) t.push_back(*i);
        t.push_back(*it);
        return t;
    }
    
    class number
    {
        private:
        #define y (*this)
        #define checknan() (isnan()||x.isnan())

        bool sign;vector <uint> v;
        
           
            number(const bool &flag1,vector <uint> &c,const bool &flag2)
            {
                sign=flag1;
                if(!flag2) v=checkv(c);
                else{
                    v.reserve(c.capacity());
                    for(uint it:c) v.push_back(it);
                }           
            }
            inline uint size()const{
                return v.size();
            }
            inline uint operator [] (const uint &x)const{
                return v[x];
            }
            inline number nan()const{
            return number('#');
        }
        
        
        public:
        //类型转化

        number()
        {
            sign=false;
            v.clear();
            v.push_back(0);
        }
        number(int x)
        {
            v.clear();
            x<0 ? sign=true,x=-x : sign=false;
            v.reserve(2);
            v.push_back(x);
        }
        number(long long x)
        {
            v.clear();
            x<0 ? sign=true,x=-x : sign=false;
            v.reserve(4);
            v.push_back(uint(x));
            if(x>>32) v.push_back(x>>32);
        }
        number(const bool &flag,const vector <uint> &c)
        {
            sign=flag;
            v=checkv(c);
        }
        number(const char *c)//最后一个是空格
        {
            const uint x=strlen(c);
            for(uint i=0 ; i<x ;++i) if(!isdigit(c[i])) {puts("Error");return;}
            number b=1;
            /*
            for(uint i=x ; i-- ;b=b*10)
            {   
                if(c[i]=='0') continue;
                y=y+b*(c[i]-'0');
            }*/
        }

        //逻辑运算符,涉及nan永远false

        inline bool operator !(void)const{
            //if(isnan()) return false;
            if(v.size()==1&&*v.cbegin()==0) return true;
            else return false;
        }
        inline bool operator >(const number &x)const{
            if(checknan()) return false;
            if(sign!=x.sign) return sign<x.sign;
            if(size()!=x.size()) return sign ? size()<x.size() : size()>x.size();
            for(uint i=size();i--;)
                if(v[i]!=x[i]) return sign ? v[i]<x[i] : v[i]>x[i];
            return false;
        }
        inline bool operator >=(const number &x)const{
            if(checknan()) return false;
            if(sign!=x.sign) return sign<x.sign;
            if(size()!=x.size()) return sign ? size()<x.size() : size()>x.size();
            for(uint i=size();i--;)
                if(v[i]!=x[i]) return sign ? v[i]<x[i] : v[i]>x[i];
            return true;
        }
        inline bool operator <(const number &x)const{
            if(checknan()) return false;
            if(sign!=x.sign) return sign>x.sign;
            if(size()!=x.size()) return sign ? size()>x.size() : size()<x.size() ;
            for(uint i=size();i--;)
                if(v[i]!=x[i]) return sign ? v[i]>x[i] : v[i]<x[i];
            return false;
        }
        inline bool operator <=(const number &x)const{
            if(checknan()) return false;
            if(sign!=x.sign) return sign>x.sign;
            if(size()!=x.size()) return sign ? size()>x.size() : size()<x.size() ;
            for(uint i=size();i--;)
                if(v[i]!=x[i]) return sign ? v[i]<x[i] : v[i]>x[i];
            return true;
        }
        inline bool operator ==(const number &x)const{
            if(checknan()) return false;
            if(sign==x.sign&&v==x.v)return true;
            else return false;
        }
        inline bool operator !=(const number &x)const{
            if(checknan()) return false;
            if(sign==x.sign&&v==x.v)return false;
            else return true;
        }
        
        //位运算符

        inline number operator <<(const long long &x)const
        {
            if(isnan()||!y||!x)return y;
            if(x<0) return y>>(-x); 
            const uint m=x>>5,r=x&31,siz=(m+v.size()+(((*--v.cend())>>(32-r))>0));
            vector <uint> c;
            c.reserve(maxsize(siz));
            c.resize(m,0);
            if(!r){
                for(uint i:v) c.push_back(i);
            }
            else {
                unsigned long long t=0; 
                for(uint i:v)
                {
                    t=(t>>32)+(((unsigned long long)i)<<r);
                    c.push_back(uint(t));
                }
                if(t>>32) c.push_back(t>>32);
            }
            return number(sign,c,1);
        }
        inline number operator >>(const long long &x)const{
            if(isnan()||!y||!x)return y;
            if(x<0) return y<<(-x); 
            const uint m=x>>5,r=x&31;
            const int siz=(v.size()-m-((*--v.cend())<(1<<r)));
            //cout << siz <<" "<< maxsize(siz) <<endl;
            if(siz<=0) return 0;
            number c=nan();
            c.v.reserve(maxsize(siz));
            if(!r){
                for(uint i=m ; i<v.size() ;++i) c.v.push_back(v[i]);
            }
            else{//前m位没了
                unsigned long long t=v[m];t<<=(32-r);
                for(uint i=m+1 ; i<v.size() ;++i)
                {
                    t=(t>>32)+(v[i]<<(32-r));
                    c.v.push_back(uint(t));
                }
                if(t>>32) c.v.push_back(t>>32);
            }
            //cout<< c.v.capacity() <<endl;
            return c;
        }

        
        //+-*/%运算符

        inline number operator -(void)const{
            number c=y;
            c.sign=!sign;
            return c;
        }
        inline number operator +(const number &x)const{
            if(checknan())return nan();
        }
        inline number operator -(number x)const{
            return y+(-x);
        }
        inline number operator *(const number &x)const{

        }
        inline number operator /(const number &x)const{
            if(checknan()||!x) return nan();
        }
        //奇怪的函数



        //测试输出
        void print()const{
            printf("vector:");
            if(isnan())  printf("Not a number! ");
            else if(!y)  printf("0 ");
            else 
            {
                if(sign) putchar('-');
                for(uint it:v) printf("%u ",it);   
            }
            printf("size:%u capacity:%u\n",v.size(),v.capacity());
        }
        inline bool isnan()const{
            if(v.empty()) return true;
            return false;
        }
    };
const number _zero=0;
const number NaN=_zero/0;

}



using namespace std;
typedef long long ll;




int main()
{
    /*测试checkv  通过
    {    vector <uint> v;
        int n;while(cin>>n&&n>0){
            v.clear();
            v.resize(n);
            for(int i=0 ; i<n ; ++i) cin>>v[i];
            v=checkv(v);
            for(int i=0 ; i<v.size() ; ++i) cout<<v[i]<<" ";
            cout<<endl;}

    }
    */
    
    number c=2,z={1,vector <uint>{1,-1u}};
    (c<<(-1)).print();
    (c<<(-100)).print();
    //cout << c.isnan() << " "<<NaN.isnan()<< " " <<endl;
    return 0;
}