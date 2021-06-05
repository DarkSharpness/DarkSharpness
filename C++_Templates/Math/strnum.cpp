#include <cstring>
#include <string>
#include <iostream>
typedef long long ll;

namespace std{

class strnum
{  
    #define number strnum
    #define _Y (*this)
    string str;//Number array.
    bool sign;//Sign of the number. 0/1:positive/negative
    /**
     * @brief Construct a new strnum object with certain command.
     * 
     * @param _C Command input.
     * @param _X Param of certain command.
     */
    inline number(const char &_C,const size_t &_X)
    {
        switch(_C)
        {
            case '#':
                str.reserve(_X);
                break;
            case '$':
                str.resize(_X);
                break;
            default:
                ;
        }
    }
    //return str.size()
    inline size_t size()const{
        return str.size();
    }
    
    public:
    //Type switching operators.

    inline operator bool()const{
        if(str.size()==1&&str.front()=='0') return false;
        else return true; 
    }

    //Bool type operator.

    inline bool operator !(void)const{
        if(str.size()==1&&str.front()=='0') return true;
        else return false; 
    }
    inline bool operator <(const number &_X)const
    {
        if(isnan()||_X.isnan()) return false;
        if(_X.sign!=sign) return sign>_X.sign;
        if(size()!=_X.size()) 
            return sign ? //negative ? reverse : normal
            size() > _X.size() : size() < _X.size();
        for(size_t i=size(); i-- ; )
            if(str[i]!=_X.str[i])
                return sign ? //negative ? reverse : normal
                str[i] > _X.str[i] : str[i] <_X.str[i] ;
        return false;   //equal
    }
    inline bool operator <=(const number &_X)const
    {
        if(isnan()||_X.isnan()) return false;
        if(_X.sign!=sign) return sign>_X.sign;
        if(size()!=_X.size()) 
            return sign ? //negative ? reverse : normal
            size() > _X.size() : size() < _X.size();
        for(size_t i=size(); i-- ; )
            if(str[i]!=_X.str[i])
                return sign ? //negative ? reverse : normal
                str[i] > _X.str[i] : str[i] <_X.str[i] ;
        return true;   //equal
    }
    inline bool operator >(const number &_X)const
    {
        if(isnan()||_X.isnan()) return false;
        if(_X.sign!=sign) return sign<_X.sign;
        if(size()!=_X.size()) 
            return sign ? //negative ? reverse : normal
            size() < _X.size() : size() > _X.size();
        for(size_t i=size(); i-- ; )
            if(str[i]!=_X.str[i])
                return sign ? //negative ? reverse : normal
                str[i] < _X.str[i] : str[i] > _X.str[i] ;
        return false;   //equal
    }
    inline bool operator >=(const number &_X)const
    {
        if(isnan()||_X.isnan()) return false;
        if(_X.sign!=sign) return sign<_X.sign;
        if(size()!=_X.size()) 
            return sign ? //negative ? reverse : normal
            size() < _X.size() : size() > _X.size();
        for(size_t i=size(); i-- ; )
            if(str[i]!=_X.str[i])
                return sign ? //negative ? reverse : normal
                str[i] < _X.str[i] : str[i] > _X.str[i] ;
        return true;   //equal
    }
    inline bool operator ==(const number &_X)const{
        if(isnan()||_X.isnan()) return false;
        return sign==_X.sign && str==_X.str ?
            true : false;
    }
    inline bool operator !=(const number &_X)const{
        if(isnan()||_X.isnan()) return false;
        return sign!=_X.sign || str!=_X.str ?
            true : false;
    }
    

    //Special functions.
#ifdef _GLIBCXX_IOSTREAM

    //Print out the number in human order.
    inline void print()const{
        if(isnan()) {puts("Not A Number!");return;}
        if(sign) putchar('-');
        for(auto it=str.rbegin();it!=str.rend() ; ++it)
            putchar(*it);
    }

    inline void print(const size_t &x)const{

    }
#endif
    //Judge if the number is a NAN.
    inline bool isnan()const{
        return str.empty() ? true:false ;
    }
    //Const iterator to the first element.(Highest bit)
    inline auto begin()const{
        return str.crbegin();
    }
    //Const iterator to the last element.(1 past the lowest bit)
    inline auto end()const{
        return str.crend();
    }



    //Initializing functions.

    //Initialize with a const char *.
    inline number(const char * const & c)
    {
        str.clear();
        size_t len=strlen(c);
        str.reserve(strlen(c));
        for( ; len-- ; )
            str.push_back(c[len]);
    }
    
    inline number(int x)
    {
        if(!x) {sign=false;str.push_back('0');return;}
        else if(x<0) x=-x,sign=true;
        else sign=false;
        
        while (x){
            str.push_back(48+x%10);
            x/=10;
        }
    }
    
    inline number(long long x)
    {
        if(!x) {sign=false;str.push_back('0');return;}
        else if(x<0) x=-x,sign=true;
        else sign=false;

        while (x){
            str.push_back(48+x%10);
            x/=10;
        }
    }
    
    #undef number
};

}
using namespace std;
strnum x(1);


int main()
{

    return 0;
}