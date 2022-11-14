#ifndef _DARK_INOUT_CC_
#define _DARK_INOUT_CC_

#include <stdio.h> // standard inout is required
#include "../include/basic.h"


namespace dark {

/// @brief  Read a signed integer.
/// @tparam integer Signed integer type,default int64_t.
/// @return The signed integer which has been read.
template <class integer = int64_t>
integer Fread_s(void) {
    int  ch;
    bool flag = false;
    while(!isdigit(ch = getchar()) && ch != EOF) {
        if(ch == '-') {flag ^= true;}
    }
    integer dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return flag ? -dst : dst;
}

/// @brief Read a signed integer.
/// @param dst Where the signed integer will be written into.
template <class integer>
void Fread_s(integer &dst) {
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
    if(flag) dst = -dst;
}


/// @brief  Read a unsigned integer.
/// @tparam integer Unsigned integer type,default uint64_t.
/// @return The unsigned integer which has been read.
template <class integer = uint64_t>
integer Fread_u(void) {
    int  ch;
    while(!isdigit(ch = getchar()) && ch != EOF);
    integer dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return dst;
}


/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
template <class integer>
void Fread_u(integer &dst) {
    int  ch;
    while(!isdigit(ch = getchar()) && ch != EOF);
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}
/// @brief Read a signed integer. 
/// If you want to read a char,use getchar() instead.
/// @param dst Where the signed integer will be written into.
void Fread(int8_t  &dst)  {Fread_s(dst);}
/// @brief Read a signed integer. 
/// @param dst Where the signed integer will be written into.
void Fread(int16_t &dst)  {Fread_s(dst);}
/// @brief Read a signed integer. 
/// @param dst Where the signed integer will be written into.
void Fread(int32_t &dst)  {Fread_s(dst);}
/// @brief Read a signed integer. 
/// @param dst Where the signed integer will be written into.
void Fread(int64_t &dst)  {Fread_s(dst);}
/// @brief Read an unsigned integer.
/// If you want to read in a char,use getchar() instead.
/// @param dst Where the unsigned integer will be written into.
void Fread(uint8_t  &dst) {Fread_u(dst);}
/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
void Fread(uint16_t &dst) {Fread_u(dst);}
/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
void Fread(uint32_t &dst) {Fread_u(dst);}
/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
void Fread(uint64_t &dst) {Fread_u(dst);}

template <class integer>
void Fwrite_s(integer dst) {
    
    
}




}

#endif