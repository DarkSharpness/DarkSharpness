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
inline void Fread_s(T &dst) {
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

/// @brief Read a char object like getchar does 
inline void Fread_c(char &ch) {
    ch = getchar();
}

// A series of smart fast read for integers/signs/char *

// Fast read-in.
inline void Fread(int16_t &dst) {
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
// Fast read-in.
inline void Fread(int32_t &dst) {
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
// Fast read-in.
inline void Fread(int64_t &dst) {
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
// Fast read-in.
inline void Fread(uint16_t &dst) {
    char ch;
    while(!isdigit(ch = getchar()));
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}
// Fast read-in.
inline void Fread(uint32_t &dst) {
    char ch;
    while(!isdigit(ch = getchar()));
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}
// Fast read-in.
inline void Fread(uint64_t &dst) {
    char ch;
    while(!isdigit(ch = getchar()));
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}

// Fast read-in
inline void Fread(int8_t &ch) {
    ch = getchar();
}
// Fast read-in
inline void Fread(uint8_t &ch) {
    ch = getchar();
}



/**
 * @brief Fast print-out for signed integers. \n 
 * Suitable for OIers.
 * 
 * @param val The value to be printed.
 */
template <class T>
inline void Fwrite_s(T val) {
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

/**
 * @brief Read in multiple integers.
 * 
 */
template <class T,class ...V> 
inline void read(T &arg,V &...args) {
    Fread(arg);
    read(args...);
}


//Print out a certain string.
inline void write_s(const char * str) {
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
inline void write_s(const char * str,T arg,V ...args) {
    while(*str != '#') putchar(*(str++));
    Fwrite(arg);
    write_s(++str,args...);
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
    bool isEOF;     // reach EOF = true
    bool sign_mode; // unsigned  = true
    using iref = in_stream &;
    public:

    /// @brief Reserve the space you need for 
    /// a char * style string before-hand.
    iref operator >>(char *str) {
        char ch = getchar();
        if(ch == EOF) { // end of a file
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

    /// @brief Read in a single char,just like getchar().
    iref operator >>(char &c) {
        c = getchar();
        if(c == EOF) { //end of a file
            isEOF = true;
            return *this;
        }
        return *this;
    }

    /// @brief Default read-in for number types.
    /// Whether it's signed depend on sign mode.
    /// For maximum speed, use read()/read_u() instead.
    template <class T>
    iref operator >>(T &dst) {
        if(sign_mode == false) {
            Fread(dst);
        } else {
            Fread_u(dst);
        }
        return *this;
    }

    
    /// @return bool true if end of file is reached
    operator bool() const{
        return !isEOF;
    }

    /// @brief Switch sign mode between signed/unsigned
    inline void switch_mode() {
        sign_mode ^= true;
    }
    /// @brief Switch sign mode to signed/unsigned
    /// @param mode 0(false):signed  1(true):unsigned
    inline void switch_mode(bool mode) {
        sign_mode = mode;
    }

    /// @brief 
    in_stream() {
        sign_mode = isEOF = false;
    }
};

class out_stream {
    using oref = out_stream&;
    bool sign_mode;
    public:
    oref operator <<(const char * str) {
        while(*str != 0) {
            putchar(*(str));
            ++str;
        }
        return *this;
    }
    oref operator <<(char * str) {
        while(*str != 0) {
            putchar(*(str));
            ++str;
        }
        return *this;
    }
    oref operator <<(const char _ch) {
        putchar(_ch);
        return *this;
    }
    oref operator <<(oref _O) {
        putchar('\n');
        return *this;
    }
    
    /// @brief Write an signed/unsigned number.
    /// Whether it's signed depend on sign mode.
    /// For maximum speed, use write()/write_u() instead.
    template <class T>
    oref operator <<(const T &arg) {
        Fwrite(arg);
        return *this;
    }

    /// @brief Switch sign mode between signed/unsigned
    inline void switch_mode() {
        sign_mode ^= true;
    }
    /// @brief Switch sign mode to signed/unsigned
    /// @param mode 0(false):signed  1(true):unsigned
    inline void switch_mode(bool mode) {
        sign_mode = mode;
    }

    out_stream() {
        sign_mode = false;
    }
};

in_stream  din ; // cin-like  input 
out_stream dout; // cout-like output
out_stream endd; // start a new line

}
#endif