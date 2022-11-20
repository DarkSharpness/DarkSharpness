#include <iostream>
#include <string>

namespace dark{
class calendar {
  private:
//   public:
    constexpr static int month[2][12] = {
        31,28,31,30,31,30,
        31,31,30,31,30,31,

        31,29,31,30,31,30,
        31,31,30,31,30,31,
    };
    constexpr static int pre[2][12] = {
        31,59,90,120,151,181,
        212,243,273,304,334,365,

        31,60,91,121,152,182,
        213,244,274,305,335,366
    };
    int time;
    inline int getDay  () const{
        return time % 100;
    }
    inline int getMonth() const{
        return (time / 100) % 10000;
    }
    inline int getYear () const {
        return time / 10000;
    }
    static inline bool isRun(int tmp) {
        return (!(tmp % 400)) || (!(tmp % 4) && (tmp % 100));
    }
    inline int getDelta(const calendar &rhs) const{
        int tmp0 = getYear() - 1,tmp1 = rhs.getYear() - 1;
        int delta = (tmp1 - tmp0) * 365 
                   + tmp1 % 4   - tmp0 % 4
                   - tmp1 % 100 + tmp0 % 100
                   + tmp1 % 400 - tmp0 % 400;
        ++tmp0; ++tmp1;
        delta += pre[isRun(tmp1)][rhs.getMonth() - 1];
               - pre[isRun(tmp0)][    getMonth() - 1];
        delta += rhs.getDay() - getDay(); 
        return delta;
    }
    inline calendar &add(const int delta) {
        calendar test((time / 10000 + delta / 365),1,1);
        while(getDelta(test) < delta) {
            test.time += 10000;
        }
        test.time -= 10000;
        while(test.time <= 12 && getDelta(test) < delta) {
            test.time += 100;
        }
        test.time -= 100;
        test.time += delta - getDelta(test);
    }
    inline calendar &sub(int delta) {

    }

  public:
    inline bool operator <(const calendar &rhs) const{
        return time < rhs.time;
    }
    inline bool operator >(const calendar &rhs) const{
        return time > rhs.time;
    }
    inline bool operator <=(const calendar &rhs) const{
        return time <= rhs.time;
    }
    inline bool operator >=(const calendar &rhs) const{
        return time >= rhs.time;
    }
    inline bool operator ==(const calendar &rhs) const{
        return time == rhs.time;
    }
    inline bool operator !=(const calendar &rhs) const{
        return time != rhs.time;
    }
    inline calendar &operator ++(void) {
        if(getDay() < month[isRun(getYear())][getMonth() - 1]) ++time;
        else if(getMonth() < 12) {
            time = time / 100 + 1;
            time = time * 100 + 1;
        } else {
            time = time / 10000 + 1;
            time = time * 10000 + 101;
        }
    }

    inline calendar &operator +=(int delta) {
        if(delta == 0) return *this;
        else if(delta > 0)  return add(delta);
        else                return sub(delta);

    }



    inline calendar &operator --(void) {
        if(getDay() > 1) --time;
        else if(getMonth() > 1) {
            time = time / 100 - 1 ;
            time = time * 100 + month[isRun(time / 100)][time % 100 - 1];
        } else {
            time = time / 10000 - 1;
            time = time * 10000 + 1231;
        }
    }

    calendar() {
        time = 10101;
    }

    calendar(const std::string &str) {
        time = 0;
        for(char _ch : str) {
            if(!isdigit(_ch)) continue;
            time = time * 10 + (_ch ^ '0');
        }
    }
    calendar(int year,int month,int day) {
        time = year * 10000 + month * 100 + day;
    }


};

const calendar operator "" _C(const char *ptr,size_t n) {
    return calendar(ptr);
}



}
using Calendar = dark::calendar;

signed main() {
    return 0;
}