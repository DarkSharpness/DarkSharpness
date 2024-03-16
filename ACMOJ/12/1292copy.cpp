#include <iostream>
#include <string>

#define ca Calendar

const int day_sum_month[2][13] = {{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
                                  {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}};

inline bool is_run(int year) { return (year % 4 == 0 && year % 100) || (year % 400 == 0); }

inline int year_to_cnt(const int &year) { return year * 365 + year / 4 - year / 100 + year / 400; }
inline int month_to_cnt(const bool &is_run, const int &month) { return day_sum_month[is_run][month]; }
inline int day_to_cnt(const int &day) { return day; }

int to_int(const std::string &s);
std::string to_str(int cnt);

class Calendar {
  private:
    int cnt;

  public:
    Calendar() : cnt(0) {}
    Calendar(const int &year, const int &month, const int &day)
        : cnt(year_to_cnt(year - 1) + month_to_cnt(is_run(year), month - 1) + day_to_cnt(day)) {
            // std::cout << cnt << '\n';
        }
    Calendar(const std::string &s) { *this = Calendar(to_int(s.substr(0, 4)), to_int(s.substr(5, 2)), to_int(s.substr(8, 2))); }

  private:
    Calendar(const int &cnt) : cnt(cnt) {}

  public:
    friend bool operator==(const ca &x, const ca &y) { return x.cnt == y.cnt; }
    friend bool operator!=(const ca &x, const ca &y) { return x.cnt != y.cnt; }
    friend bool operator>=(const ca &x, const ca &y) { return x.cnt >= y.cnt; }
    friend bool operator<=(const ca &x, const ca &y) { return x.cnt <= y.cnt; }
    friend bool operator>(const ca &x, const ca &y) { return x.cnt > y.cnt; }
    friend bool operator<(const ca &x, const ca &y) { return x.cnt < y.cnt; }

  public:
    friend ca operator+(ca x, const int &y) { return ca(x.cnt + y); }
    friend ca operator-(ca x, const int &y) { return ca(x.cnt - y); }

    ca &operator+=(const int &y) { return *this = ca(cnt + y); }
    ca &operator-=(const int &y) { return *this = ca(cnt - y); }

    ca &operator++() { return *this += 1; }
    ca &operator--() { return *this -= 1; }
    ca operator++(int) { return Calendar((*this += 1).cnt - 1); }
    ca operator--(int) { return Calendar((*this -= 1).cnt + 1); }

    friend int operator-(const ca &x, const ca &y) { return x.cnt - y.cnt; }

  public:
    operator std::string() { return to_str(cnt); }
    int getday() { return cnt % 7; }
};

int to_int(const std::string &s) {
    int res = 0;
    for (int i = 0; i < s.size(); i++)
        res = res * 10 + s[i] - '0';
    return res;
}
std::string to_str(int cnt) {
    int year = 0, month = 0;
    for (int i = 15; ~i; i--)
        if (year_to_cnt(year | (1 << i)) < cnt)
            year |= (1 << i);
    cnt -= year_to_cnt(year);
    year++;
    // std::cout << cnt ;
    for (; day_sum_month[is_run(year)][month] < cnt; month++)
        ;
    cnt -= day_sum_month[is_run(year)][month - 1];
    char out_str[11];
    sprintf(out_str, "%04d-%02d-%02d", year, month, cnt);
    return static_cast<std::string>(out_str);
}
std::istream &operator>>(std::istream &in, ca &x) {
    std::string s;
    in >> s;
    x = s;
    return in;
}
std::ostream &operator<<(std::ostream &out, ca x) {
    out << std::string(x);
    return out;
}
const Calendar operator""_C(const char *col, size_t n) { return Calendar(std::string(col)); }


//4
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    Calendar cend = Calendar("1005-12-31");
    Calendar c(1000,1,1);
    Calendar startc;
    freopen("1292.txt","w",stdout);
    startc = c;
    for (; c < cend; c+=2) {
        cout << string(c++) << endl;
        cout << (++c).getday() << endl;
    }
    for (; c >= startc; c-=10) {
        cout << string(c--) << endl;
        cout << (--c).getday() << endl;
    }
    c = Calendar("0001-01-01")+1400;
    Calendar cc = c - 1400;
    for (; cc < c + 1400; ++cc) {
        cout << (cc > c) << (cc == c) << (cc < c) << (cc == c) << (cc != c);
        cout << (cc-c);
    }
}