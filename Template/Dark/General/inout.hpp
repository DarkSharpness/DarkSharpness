#ifndef _DARK_MATHS_HPP_
#define _DARK_MATHS_HPP_

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

/* Equal to getchar(). */
char &Fread(char &dst) {return dst = getchar();}

/* Equal to scanf*/
float  &Fread(float &dst)  {scanf("%f",&dst); return dst;}
/* Equal to scanf*/
double &Fread(double &dst) {scanf("%lf",&dst);return dst;}



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

/* Read into a given range. */
template <class Iterator>
void readRange(Iterator begin,Iterator end) {
    while(begin != end) {
        read(*begin);
        ++begin;
    }
}
/* Read into a given range. */
template <class Iterator>
void readRange(Iterator begin,size_t len) {
    while(len--) {
        read(*begin);
        ++begin;
    }
}
/* Read into a given range. */
template <class Container>
void readRange(Container &_C) {
    for(auto &it : _C) {Fread(it);}
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



/* Write a char * string. */
void Fwrite(char *ptr) {
    printf("%s",ptr);
}
/* Write a char * string. */
void Fwrite(const char *ptr) {
    printf("%s",ptr);
}
/* Write a single char. */
void Fwrite(char _ch) {putchar(_ch);}

/* Write a float. */
void Fwrite(float src) {printf("%f",src);}

/* Write a double. */
void Fwrite(double src) {printf("%lf",src);}

/* Ending. */
template <class integer>
void write(const integer &arg) {
    Fwrite(arg);
}

/* Print a series of integers separated by space.
   Note that there's no '\\n' in the end. */
template <class integer,class ...others>
void write(const integer &arg,const others &...args) {
    Fwrite(arg);
    putchar(' ');
    write(args...);
}

/* Print out elements within a range.
   Each element separated by space. */
template <class Iterator>
void writeRange(Iterator begin,Iterator end) {
    if(begin == end) return;
    Fwrite(*begin);
    while(++begin != end) {
        putchar(' ');
        Fwrite(*begin);
    }
}

/* Start a new line. */
void endl(){putchar('\n');}

/* Print out elements within a range */
template <class Iterator>
void writeRange(Iterator begin,size_t len) {
    if(!len) return;
    Fwrite(*begin);
    while(--len) {
        putchar(' ');
        Fwrite(*(++begin));
    }
}

/* Write the elements in the Container. */
template <class Container>
void writeRange(const Container &_C) {
    for(const auto &it : _C) {Fwrite(it);putchar(' ');}
    putchar('\b');
}



}


#endif