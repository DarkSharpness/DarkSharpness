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
inline constexpr void Fread(T &dst) {
    char ch = getchar();
    bool flag = false;
    while(!isdigit(ch)) {
        if(ch == '-') flag = true;
        ch = getchar();
    }
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) dst *= -1;
}

/**
 * @brief Fast read-in for unsigned integers. \n 
 * Suitable for OIers. 
 * 
 * @param dst The variable to be written into.
 */
template <class T>
inline void Fread_u(T &dst) {
    char ch;
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
    char ch[sizeof(T)<<3];
    int  cnt = -1;
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
    char ch[sizeof(T)<<3];
    int  cnt = -1;
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
inline void read(T &arg,V &...args) {
    Fread(arg);
    read(args...);
}

/**
 * @brief Read in multiple unsigned integers.
 * 
 */
template <class T,class ...V> 
inline void read_u(T &arg,V &...args) {
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

class in_stream {
    mutable bool isEOF;
    char func;
    using icref = const in_stream &;
    public:
    /// @brief Reserve the space you need before-hand.
    icref operator >>(char *str) const{
        char ch = getchar();
        if(ch == EOF) { //end of a file
            isEOF = true;
            return *this;
        }
        while(ch != '\0' &&
              ch != '\n' && 
              ch != EOF) {
            *(str++) = ch ;
            ch = getchar();
        }
        *str = 0;
        return *this;
    }
    /// @brief Read in a char.
    icref operator >>(char &c) const{
        char ch = getchar();
        if(ch == EOF) { //end of a file
            isEOF = true;
            return *this;
        }
        c = ch;
        return *this;
    }
    /// @brief Default read-in for signed number types.
    template <class T>
    icref operator >>(T &dst) const{
        char ch = getchar();
        if(ch == EOF) {
            isEOF = true;
            return *this;
        }
        bool flag = false;
        while(!isdigit(ch)) {
            if(ch == '-') flag = true;
            ch = getchar();
        }
        dst = 0;
        while(isdigit(ch)) {
            dst = dst * 10 + (ch ^ '0');
            ch  = getchar();
        }
        if(flag) dst *= -1;
        return *this;
    }

    /// @return bool true if end of file is reached
    operator bool() const{
        return !isEOF;
    }
    in_stream() {
        isEOF = false;
    }
};

class out_stream {
    using ocref = const out_stream&;
    public:
    ocref operator <<(const char * str) const{
        while(*str != 0) {
            putchar(*(str));
            ++str;
        }
        return *this;
    }
    ocref operator <<(char * str) const{
        while(*str != 0) {
            putchar(*(str));
            ++str;
        }
    }
    ocref operator <<(const char _ch) const{
        putchar(_ch);
    }
    ocref operator <<(ocref _O) const{
        putchar('\n');
    }
    
    template <class T>
    ocref operator <<(const T &arg) const{
        Fwrite(arg);
        return *this;
    }
 
    out_stream() {
    }
};

in_stream  din ; // cin-like  input 
out_stream dout; // cout-like output
out_stream endd; // start a new line

}
#endif