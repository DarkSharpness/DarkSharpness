#include <iostream>
#include <cstring>
#define size_t int64_t
inline size_t ToInt(const char *ptr) {
    size_t ret = 0;
    while(isdigit(*ptr)) { ret = ret * 10 + ((*ptr) ^ '0');++ptr; }
    return ret;
}
class Calendar {
  private:
    static constexpr size_t Month[2][13] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
        0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366
    };
    size_t dfn;
    Calendar(size_t tim) : dfn(tim) {}
  public:
    static size_t GetYear(size_t year) {return year * 365 + year / 4 - year / 100 + year / 400;}
    static size_t GetMonth(size_t month,bool type) {return Month[type][month];}
    static bool isRun(size_t year) {return !(year % 400) || ((year % 100) && !(year % 4));}
    Calendar() : dfn(0) {}
    inline size_t getday() {return dfn % 7;}
    Calendar(size_t year,size_t month,size_t day) {dfn = GetYear(year - 1) + GetMonth(month - 1,isRun(year)) + day;}
    friend bool operator ==(const Calendar &x, const Calendar &y) {return x.dfn == y.dfn;}
    friend bool operator !=(const Calendar &x, const Calendar &y) {return x.dfn != y.dfn;}
    friend bool operator >=(const Calendar &x, const Calendar &y) {return x.dfn >= y.dfn;}
    friend bool operator <=(const Calendar &x, const Calendar &y) {return x.dfn <= y.dfn;}
    friend bool operator > (const Calendar &x, const Calendar &y) {return x.dfn >  y.dfn;}
    friend bool operator < (const Calendar &x, const Calendar &y) {return x.dfn <  y.dfn;}
    Calendar &operator ++() {++dfn;return *this;}
    Calendar &operator --() {--dfn;return *this;}
    Calendar operator ++(int) {++dfn;return Calendar(dfn - 1);}
    Calendar operator --(int) {--dfn;return Calendar(dfn + 1);}
    friend int64_t  operator -(const Calendar &x,const Calendar &y) {return x.dfn - y.dfn;}
    friend Calendar operator +(const Calendar &x,size_t tim) {return Calendar(x.dfn + tim);} 
    friend Calendar operator -(const Calendar &x,size_t tim) {return Calendar(x.dfn - tim);} 
    friend Calendar &operator +=(Calendar &x,size_t tim) {x.dfn += tim;return x;} 
    friend Calendar &operator -=(Calendar &x,size_t tim) {x.dfn -= tim;return x;} 
    operator std::string() const{
        size_t delta = dfn;
        size_t year = delta / 365 + 2;
        while(Calendar::GetYear(year) >= delta) --year;
        delta -= GetYear(year);
        const bool type = Calendar::isRun(++year);
        size_t month = 0;
        while(Calendar::GetMonth(month,type) < delta) ++month;
        delta -= Month[type][month - 1];
        char buffer[11];
        sprintf(buffer,"%04lld-%02lld-%02lld",year,month,delta);
        return buffer;
    }
    Calendar(const char *str) {*this = Calendar(ToInt(str + 0),ToInt(str + 5),ToInt(str + 8));}
    friend std::istream &operator >>(std::istream &is,Calendar &x) {
        std::string buffer;
        is >> buffer; x = Calendar(buffer.c_str());
        return is;
    }
    friend std::ostream &operator <<(std::ostream &os,const Calendar &x) {
        os << std::string(x);
        return os;
    }
};
const Calendar operator "" _C( const char *col, uint64_t n) {return Calendar(col);}
