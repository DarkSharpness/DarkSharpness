#ifndef _DARK_IO_H_
#define _Dark_IO_H_

#include <General/basic.h>
#include <stdio.h>

namespace dark{

//typedef int value_type;

/**
 * @brief Fast input for unsigned integer type.\n 
 * For example, unsigned int,unsigned long long,__uint128_t.......\n 
 * Or any signed integer type without '-' input.
 * @tparam Unsigned _Integer_Type
 * @return The value input.
 */
template <typename value_type>
value_type Fread_unsigned(){
    register value_type ans = 0;
    register char ch        = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        ans = ans * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return ans;
}
/**
 * @brief Fast input for signed integer type.\n 
 * For example, short,int,long long,__int128_t.......
 * @tparam Unsigned _Integer_Type
 * @return The value input.
 */
template<typename value_type>
value_type Fread(){
    register value_type ans = 0;
    register char ch        = getchar();
    register bool flag      = false;
    while(ch < '0' || ch > '9') {
        if(ans == '-') flag = true;
        ch = getchar();
    }
    while(ch >= '0'&&ch <= '9') {
        ans = ans * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return flag ? -ans : ans;
}


/**
 * @brief Fast out put for unsigned integer type or
 * any signed integer type which is > 0
 * @tparam Unsigned_Integer_Type
 * @param X  The number to be printed. 
 */
template <typename value_type>
void Fwrite_unsigned(value_type X){
    if(!X) putchar('0'); 
    static short cnt    = -1;
    static char  ch[int(sizeof(value_type)*2.5)+1];
    while(X) {
        ch[++cnt] = (X%10) ^ '0';
        X/=10;
    }
    while(cnt != -1) {
        putchar(ch[cnt--]);
    }
}
/**
 * @brief Fast out put for signed integer type.
 * @tparam Signed_Integer_Type 
 * @param X  The number to be printed. 
 */
template <typename value_type>
void Fwrite(value_type X){
    if(!X) putchar('0'); 
    static short cnt    = -1;
    static char  ch[int(sizeof(value_type)*2.5)+1];
    if(X < 0) putchar('-');
    while(X) {
        ch[++cnt] = (X%10) ^ '0';
        X/=10;
    }
    while(cnt != -1) {
        putchar(ch[cnt--]);
    }
}

#define Fread_signed()  Fread()
#define Fwrite_signed() Fwrite()


}


#endif