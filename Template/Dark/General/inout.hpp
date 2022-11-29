#ifndef _DARK_INOUT_HPP_
#define _DARK_INOUT_HPP_

#include <stdio.h> // standard inout is required
#include "../include/basic.hpp"

/**
 * @brief This parts includes all basic input
 * functions for integers.
 * It's easy to use and quite effiecent for OIers.
 * 
 */
namespace dark {

/**
 * @brief Read a signed integer.
 * 
 * @param  dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
template <class integer>
integer &Fread_s(integer &dst) {
    int  ch;
    bool flag = false;
    while(!isdigit(ch = getchar()) && ch != EOF) {
        if(ch == '-') {flag ^= true;}
    }
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return flag ? dst = -dst : dst;
}


/**
 * @brief Read an unsigned integer.
 * 
 * @param  dst Where the unsigned integer will be written into.
 * @return The unsigned number which has been read.
 */
template <class integer>
integer &Fread_u(integer &dst) {
    int  ch;
    while(!isdigit(ch = getchar()) && ch != EOF);
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return dst;
}


/**
 * @brief Read a signed integer. 
 * If you want to read a char,use getchar() instead.
 * 
 * @param dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
int8_t  &Fread(int8_t  &dst)  {return Fread_s(dst);}
/**
 * @brief Read a signed integer. 
 * 
 * @param dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
int16_t &Fread(int16_t &dst)  {return Fread_s(dst);}
/**
 * @brief Read a signed integer. 
 * 
 * @param dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
int32_t &Fread(int32_t &dst)  {return Fread_s(dst);}
/**
 * @brief Read a signed integer. 
 * 
 * @param dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
int64_t & Fread(int64_t &dst) {return Fread_s(dst);}
/**
 * @brief Read a signed integer. 
 * 
 * @param dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
uint8_t &Fread(uint8_t  &dst) {return Fread_u(dst);}
/**
 * @brief Read an unsigned integer.
 * If you want to read a char,use getchar() instead.
 * 
 * @param dst Where the unsigned integer will be written into.
 * @return The unsigned number which has been read.
 */
uint16_t &Fread(uint16_t &dst) {return Fread_u(dst);}
/**
 * @brief Read an unsigned integer.
 * 
 * @param dst Where the unsigned integer will be written into.
 * @return The unsigned number which has been read.
 */
uint32_t &Fread(uint32_t &dst) {return Fread_u(dst);}
/**
 * @brief Read an unsigned integer.
 * 
 * @param dst Where the unsigned integer will be written into.
 * @return The unsigned number which has been read.
 */
uint64_t &Fread(uint64_t &dst) {return Fread_u(dst);}


/**
 * @brief  Read an integer(signed or unsigned).
 * 
 * @tparam integer Any integer type.
 * @return The integer which has been read.
 */
template <class integer>
integer Fread() {
    integer tmp;
    return Fread(tmp);
}

/**
 * @brief  Read a signed integer.
 * 
 * @tparam integer Signed integer type,default intmax_t.
 * @return he signed integer which has been read.
 */
template <class integer = intmax_t>
integer Fread_s(void) {
    integer tmp;
    return Fread_s <integer> (tmp);
}

/**
 * @brief  Read an unsigned integer.
 * 
 * @tparam integer Unsigned integer type,default uintmax_t.
 * @return he signed integer which has been read.
 */
template <class integer = uintmax_t>
integer Fread_u(void) {
    integer tmp;
    return Fread_u <integer> (tmp);
}

/* Ending */
void read() {};

/* Read a series of integers. */
template <class integer,class ...others>
void read(integer &arg,others &...args) {
    Fread(arg);
    read(args...);
}



}


/**
 * @brief This parts includes all basic ouput
 * functions for integers.
 * It's easy to use and quite effiecent for OIers.
 * TODO: Flow control
 * 
 */
namespace dark {
/**
 * @brief  Print out integer fast.
 * 
 * @tparam integer Any integer type. You may leave it blank
 *         or set the integer type yourself. For example, 
 *         Fwrite <unsigned> (-1) will be 4294967295.
 * @param  src The number to be written.
 */
template <class integer>
void Fwrite(integer src) {
    static char ch[20];
    if(src == 0) {
        putchar('0');
    } else if(src < 0) {
        src = -src;
        putchar('-');
    }
    int32_t top = 19; 
    while(src) {
        ch[--top] = (src % 10) ^ '0';
        src /= 10;
    }
    printf("%s",ch + top);
}

/// @brief Ending.
void write() {}

/// @brief Print a series of integers separated by space.
/// Note that there's no '\\n' in the end.
template <class integer,class ...others>
void write(const integer &arg,const others &...args) {
    Fwrite(arg);
    putchar(' ');
    write(args...);
}



}

/**
 * @brief This part includes all standard inouts
 * classes for darksharpness class.
 * TODO: INOUT STREAM OPERATION
 * 
 */
namespace dark {

class istream {
  protected:
    istream() = default;

  public:
    constexpr istream(nullptr_t ptr) {}
    template <class integer>
    const istream &operator >>(integer &dst) const{
        Fread(dst);
        return *this;
    }

    const istream &operator >>(char &dst) const{
        dst = getchar();
        return *this;
    }
    const istream &operator >>(char *dst) const{
        scanf("%s",dst);
        return *this;
    }

    

};

class ostream {
  protected:  
    ostream() = default;

  public:
    explicit constexpr ostream(nullptr_t ptr) {}
    
    template <class integer>
    const ostream &operator <<(const integer &src) const{
        Fwrite(src);
        return *this;
    }
    const ostream &operator <<(char src) const{
        putchar(src);
        return *this;
    }
    const ostream &operator <<(const char* src) const{
        printf("%s",src);
        return *this;
    }
    const ostream &operator <<(char src[]) const{
        printf("%s",src);
        return *this;
    }
    
};

class basic_inout{
  private:
    basic_inout() = default;
  public:
    constexpr static istream iput = istream(nullptr);
    constexpr static ostream oput = ostream(nullptr);
};

const istream &iput  = basic_inout::iput;
const ostream &oput = basic_inout::oput;

}

#endif