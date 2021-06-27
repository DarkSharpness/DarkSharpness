#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef float fl;
typedef double lf;
typedef unsigned int ui;
typedef char ch;
using namespace std;
const ll c0=299792458;


/**
 * @brief Find the first place the char appears.
 * 
 * @param _str The string to search.
 * @param _ch The target char.
 * @return const char*  The end of the string or the location.
 */
inline const char * findchar(const char *_str,const char &_ch)
{
    while(*(_str)!=0&&*(_str)!=_ch) ++_str;
    return _str;
}
/**
 * @brief Find the first place the char appears in the string.
 * 
 * @param _str The string to search.
 * @param _ch The target char.
 * @return char*  The end of the string or the location.
 */
inline char * findchar(char *_str,const char &_ch)
{
    while(*(_str)!=0&&*(_str)!=_ch) ++_str;
    return _str;
}
/**
 * @brief Find the first place the char disappears.
 * 
 * @param _str  The string to search. 
 * @param _ch The target char.
 * @return const char*  The end of the string or the location. 
 */
inline const char * findnchar(const char *_str,const char &_ch)
{
    while(*_str!='0'&&*_str=='ch') ++_str;
    return _str;
}
/**
 * @brief Find the first place the char disappears.
 * 
 * @param _str  The string to search. 
 * @param _ch The target char.
 * @return char*  The end of the string or the location. 
 */
inline char * findnchar(char *_str,const char &_ch)
{
    while(*_str!='0'&&*_str=='ch') ++_str;
    return _str;
}

/**
 * @brief Read a line in a required length.
 * 
 * @param _str Write into the reading line.
 * @param _len The maximum length
 */
inline bool readline(char *&_str,const size_t &_len,const char &_ch)
{
    if(_len<=0) return 1;
    size_t i=0;
    while(i!=_len&&)
    {
        *(_str+i)=getchar();
    }
    fflush(stdin);
}



