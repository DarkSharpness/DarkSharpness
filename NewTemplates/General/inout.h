#include <stdio.h>
#include <ctype.h>
#include <General/basic.h>
#ifndef _DARK_INOUT_H_
#define _DARK_INOUT_H_

namespace dark {


/**
 * @brief Fast read-in for signed integers. \n 
 * Suitable for OIers. 
 * 
 * @param dst The variable to be written into.
 */
template <class T>
inline void Fread(T &dst) {
    static char ch;
    static bool flag;
    flag = false;
    while(!isdigit(ch = getchar()))
        if(ch == '-') flag = true;
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) dst *= -1,flag = false;
}

/**
 * @brief Fast read-in for unsigned integers. \n 
 * Suitable for OIers. 
 * 
 * @param dst The variable to be written into.
 */
template <class T>
inline void Fread_u(T &dst) {
    static char ch;
    while(!isdigit(ch = getchar()));
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}

/**
 * @brief Fast print-out for signed integers. \n 
 * Suitable for OIers.
 * 
 * @param val The value to be printed.
 */
template <class T>
inline void Fwrite(T val) {
    if(!val) {
        putchar('0');
        return ;
    }
    static char ch[sizeof(T)<<3];
    static int  cnt = -1;
    if(val < 0) putchar('-'),val = -val;
    while(val) {
        ch[++cnt] = (val % 10) ^ '0';
        val /= 10;
    }
    while(cnt != -1) 
        putchar(ch[cnt--]);
}

/**
 * @brief Fast print-out for unsigned integers. \n 
 * Suitable for OIers.
 * 
 * @param val The value to be printed.
 */
template <class T>
inline void Fwrite_u(T val) {
    if(!val) {
        putchar('0');
        return ;
    }
    static char ch[sizeof(T)<<3];
    static int  cnt = -1;
    while(val) {
        ch[++cnt] = (val % 10) ^ '0';
        val /= 10;
    }
    while(cnt != -1) 
        putchar(ch[cnt--]);
}

inline void read() {}
inline void read_u() {}

/**
 * @brief Read in multiple signed integers.
 * 
 */
template <class T,class ...V> 
void read(T &arg,V &...args) {
    Fread(arg);
    read(args...);
}

/**
 * @brief Read in multiple unsigned integers.
 * 
 */
template <class T,class ...V> 
void read_u(T &arg,V &...args) {
    Fread_u(arg);
    read_u(args...);
}

//Print out a certain string.
inline void write(const char * str) {
    while(*str != '\0') putchar(*(str++));
}
//Print out a certain string.
inline void write_u(const char * str) {
    while(*str != '\0') putchar(*(str++));
}


/**
 * @brief Faster print-out signed Integers.
 * Initial with char *.
 * Can't print out # !
 * 
 * @param str The location of '#' in it 
 * is where the variable is printed. 
 */
template <class T,class ...V>
inline void write(const char * str,T arg,V ...args) {
    while(*str != '#') putchar(*(str++));
    Fwrite(arg);
    write(++str,args...);
}

/**
 * @brief Faster print-out unsigned integers.
 * Initial with char *.
 * Can't print out # !
 * 
 * @param str The location of '#' in it 
 * is where the variable is printed. 
 */
template <class T,class ...V>
inline void write_u(const char * str,T arg,V...args) {
    while(*str != '#') putchar(*(str++));
    Fwrite_u(arg);
    write_u(++str,args...);
}

namespace basic_io {
class in_stream {
    public:
    template <class T>
    in_stream operator >>(T & arg) const{
        Fread(arg);
        return *this;
    }
};

class out_stream {
    public:
    out_stream operator <<(const char *str) const{
        while(*str != 0) {
            putchar(*(str));
            ++str;
        }
    }
    out_stream operator <<(const char _ch) const{
        putchar(_ch);
    }
    out_stream operator <<(out_stream _O) const {
        putchar('\n');
    }
    template <class T>
    out_stream operator <<(const T &arg) const{
        Fwrite(arg);
        return *this;
    }
};
}
const basic_io::in_stream  din ; //cin-like readin
const basic_io::out_stream dout; //cout-like write
const basic_io::out_stream dend; //equals to '\n'


}
#endif