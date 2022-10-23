#include<bits/stdc++.h>
//using namespace std;
//#define int lont long

namespace ICPC{

class instream {
    public:
    instream() { 

    }
}read;

class outstream {
    public:
    /// @brief Custom print out
    outstream & operator<<(const char *str) {
        while(*str != '\0') {
            putchar(*(str++));
        }
        return *this;
    }
    /// @brief Custom print out 
    outstream & operator<<(char ch) {
        putchar(ch);
        return *this;
    }
    outstream() {

    }
}write;

/**
 * @brief Use the last char to record the size.
 * Memory is aligned to 8.
 * Use short string optimization.
 * 
 */
class string {
    char c[24]; // data

    // const unsigned long long *
    using size_cptr = const unsigned long long*;
    public:

    inline constexpr unsigned size() const{
        return static_cast <unsigned> (c[23]); //last char
    }
    /**
     * @brief Use size_t to speed up comparation.
     * 
     * @param  str   The string to compare 
     * @return bool true if this string is less than 
     * the given string in alphabetic order
     */
    bool operator <(const string & str) const{
        
        size_cptr ptr1 = reinterpret_cast <size_cptr> (c);    
        size_cptr ptr2 = reinterpret_cast <size_cptr> (str.c);
        for(int i = 0 ; i < 3 ; ++i) {
            if(ptr1[i] < ptr2[i]) return true;
            if(ptr1[i] > ptr2[i]) return false;
        }
        return false;//the same
    }
    /// @brief custom read in 
    friend instream & operator >>(instream & read,string &str) {
        char _buff = getchar(); // read in buffer
        while(_buff == '\0' || _buff == '\n' || _buff == EOF) {
            _buff = getchar();
        }
        char *top = str.c; // current top pointer
        while(_buff != '\0' && _buff != '\n' && _buff != EOF) {
            *(top++) = _buff;
            _buff = getchar();
        }
        str.c[23] = top - str.c;
        return read;
    }
    /// @brief custom print out 
    friend outstream & operator <<(outstream & write,const string &str) {
        const char *top = str.c; // current top pointer
        while(*top != '\0') {
            putchar(*(top++));
        }
        return write;
    }
    string(const char *str) {
        char *top = c;
        while(*str != '\0') {
            *top = *str;
            ++top;
            ++str;
        }
        c[23] = top - c;
    }
    string() {
        
    }
};



}
    
using ICPC::string;
std::string str1("abc");
std::string str2("abc");
//bool cmp = str2 < str1;

signed main() {
    freopen("test.out","w",stdout);
    //std::cout << cmp << std::endl;
    std::cout << (str1 < str2);
    std::cout << (str1 < str2);
    return 0;
}