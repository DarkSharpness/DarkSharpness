#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
namespace ICPC {
    
/// @brief Custom max function 
template <class T> 
constexpr T max(const T &arg){
    return arg;
}

/// @brief Custom max function 
template <class T,class ...V> 
constexpr T max(const T &arg,const V &...args) {
    return std::max(arg,max(args...));
}

/// @brief test whether it is the end of string
inline bool isEnd(char _ch) {
    return _ch == ' ' || _ch == '\n'  ||
           _ch == EOF || _ch == '\0';
}

/// @brief Custom input class
class instream {
    public:

    instream & operator >>(char &_ch) {
        while(isEnd(_ch = getchar()));
        return *this;
    }

    /// @brief Custom read in for unsigned integers
    template <class integer>
    instream & operator >>(integer & num){
        char _buff;
        while(!isdigit(_buff = getchar()));
        num = 0;
        while(isdigit(_buff)) {
            num = num * 10 + (_buff ^'0');
            _buff = getchar();
        }
        return *this;
    }

    instream() { 
    }
}read;  // A substitue for cin

/// @brief Custom output class
class outstream {
    public:
    char buff[32]; // standard buffer for output
    char *top;      // top of current buffer
    /// @brief Custom print out for char * style string
    outstream & operator<<(const char *str) {
        while(*str != '\0') {
            putchar(*(str++));
        }
        return *this;
    }
    /// @brief Custom print out for char
    outstream & operator<<(char ch) {
        putchar(ch);
        return *this;
    }

    /// @brief Custom print out for signed integers
    template <class integer>
    outstream &operator<<(integer num) {
        if(num == 0) { // special case of 0
            putchar('0');
        } else {
            if(num < 0) {
                putchar('-');
                num = -num;
            }
            top = buff;
            while(num != 0) { // a normal fast_write template.
                (*top) = (num % 10) ^ '0';
                num /= 10;
                ++top;
            }
            while(top != buff) {
                putchar(*(--top));
            }
        }
        return *this;        
    }
    outstream() {

    }
}write; // A substitue for cout

/**
 * @brief Use the first char to record the size.
 * Memory is aligned to 8 byte(24 in total).
 * Use short string optimization designed for short strings.
 * The memory is stored conversely.
 * For example , string "abc" is stored as
 * 3 0 0 0 0 ... 'c' 'b' 'a' in the array a
 * 
 */
class string {
    char c[24]; // Data

    // const unsigned long long *
    using size_cptr = const unsigned long long*;
    public:

    /// @brief Array-style index
    inline constexpr char operator[](size_t index) {
        return c[23-index];
    }

    inline constexpr unsigned size() const{
        return static_cast <unsigned> (c[0]); //last char
    }
    /**
     * @brief Fast comparation by comparing
     * 8 byte at a time using unsigned long long.
     * 
     * @param  str   The string to compare 
     * @return bool true if this string is less than 
     * the given string in alphabetic order
     */
    bool operator <(const string &str) const{
        size_cptr ptr1 = reinterpret_cast <size_cptr> (this);    
        size_cptr ptr2 = reinterpret_cast <size_cptr> (&str);
        for(int i = 2 ; i >= 0 ; --i) {
            if(ptr1[i] < ptr2[i]) return true;
            if(ptr1[i] > ptr2[i]) return false;
        }
        return false;//the same
    }

    /**
     * @brief Fast comparation by comparing
     * 8 byte at a time using unsigned long long.
     * 
     * @param  str   The string to compare 
     * @return bool true if this string is equal to 
     * the given string in alphabetic order
     */
    bool operator ==(const string &str) const{
        size_cptr ptr1 = reinterpret_cast <size_cptr> (this);    
        size_cptr ptr2 = reinterpret_cast <size_cptr> (&str);
        for(int i = 2 ; i >= 0 ; --i) {
            if(ptr1[i] != ptr2[i]) return false;
        }
        return true;//the same
    }
    
    /**
     * @brief Fast comparation by comparing
     * 8 byte at a time using unsigned long long.
     * 
     * @param  str   The string to compare 
     * @return bool true if this string doesn't equal 
     * the given string in alphabetic order
     */
    bool operator !=(const string &str) const{
        size_cptr ptr1 = reinterpret_cast <size_cptr> (this);    
        size_cptr ptr2 = reinterpret_cast <size_cptr> (&str);
        for(int i = 2 ; i >= 0 ; --i) {
            if(ptr1[i] != ptr2[i]) return true;
        }
        return false;//the same
    }
    // If this <  str return 1.
    // If this >  str return 0.
    // If this == str return 2.
    int compare(const string & str) const {
        size_cptr ptr1 = reinterpret_cast <size_cptr> (this);    
        size_cptr ptr2 = reinterpret_cast <size_cptr> (&str);
        for(int i = 2 ; i >= 0 ; --i) {
            if(ptr1[i] < ptr2[i]) return 1;
            if(ptr1[i] > ptr2[i]) return 0;
        }
        return 2;
    }

    /// @brief Custom read in for string
    friend instream & operator >>(instream & read,string &str) {
        memset(str.c,0,sizeof(str.c)); // clear previous data.
        char _buff = getchar(); // temporary buffer
        while(isEnd(_buff)) {
            _buff = getchar();
        }
        char *top = str.c + 24; // current top pointer
        while(!isEnd(_buff)) {
            *(--top) = _buff;
            _buff = getchar();
        }
        str.c[0] = str.c + 24 - top;
        return read;
    }
    /// @brief Custom print out for string
    friend outstream & operator <<(outstream & write,const string &str) {
        const char *top = str.c + 24; // current top pointer
        while(*(--top) != '\0') {
            putchar(*top);
        }
        return write;
    }
    /// @brief Initialize with a const char* string 
    string(const char *str) {
        memset(c,0,sizeof(c));
        char *top = c + 24; // current top pointer
        while(*str != '\0') {
            *(--top) = *(str++);
        }
        c[0] = c + 24 - top;
    }
    /// @brief Initialization
    string() {
        memset(c,0,sizeof(c));
    }
};


///@brief Skip reading next string or number.
void skip_string() {
    char _buff = getchar(); // temporary buffer
    while(isEnd(_buff)) {
        _buff = getchar();
    }
    while(!isEnd(_buff)) {
        _buff = getchar();
    }
}

/// @brief Skip reading a line.
void skip_line() {
    char _buff = getchar(); // temporary buffer
    while(_buff != '\n' && _buff != EOF) {
        _buff = getchar();
    }
}

const unsigned kProblems = 26;  // Maximum number of problems

string buffer;              // Common buffer for string to read in
string buffer2;             // Common buffer for string to read in

bool gameStart  = false;    // Whether the game starts
bool gameFreeze = false;    // Whether the scoreboard is frozen
bool gameChange = false;    // Whether there is new pass AC before freezing
int  duration     = 0;      // The duration of the game
int  problemCount = 0;      // Total count of problems
int  teamCount    = 0;      // Total count of teams

// Set to judge if a name has existed.
std::set <string> nameSet;
// TeamNames in alphabetic order.
// Designed for binary_search.
std::vector <string> teamName; 
// Recording given ID's rank
// Value is 1-base , namely first = 1
std::vector <int> flushedRank;


/// @brief Simple submission class
struct submission {
    int first_AC_time;
    int submission_times;
    inline void submit() {
        ++submission_times;
    }
    inline void addAC(int time) {
        if(first_AC_time == 0) {
            first_AC_time = time;
        }
    }
    submission() {
        first_AC_time = submission_times = 0;
    }
};
// The submissions after frozen of each team
// submissions[i][j] problem[i] submission from ID[j]
std::vector <std::vector<submission>> submissions;

// status : AC = 0,WA = 1,RE = 2,TL = 3,
enum status {AC,WA,RE,TL};
status status_map[96];     // Mapping a char into a status 
// Map a status into a string
const char* status_string[4] = {
    "Accepted",
    "Wrong_Answer",
    "Runtime_Error",
    "Time_Limit_Exceed"
};

/// @brief Real time time-data of a team
struct team {
    private:
    // special vector
    struct array_4 {
        int data[4];
        array_4& operator =(const array_4& array_B) {
            memcpy(data,array_B.data,16);
            return *this;
        }
        int & operator [](size_t index_pos) {
            return data[index_pos];
        }
        int operator [](size_t index_pos) const{
            return data[index_pos];
        }
    };

    

    // pass[0]:Penalty time in all pass cases
    // pass[1 ~ 26]:Submission count before passed.
    // pass  =  0 uninitalized
    // pass  <  0 fail for -pass times
    // pass  >  0 successfull pass
    std::vector <int> pass;
    
    public:

    // History AC submit time from small to big
    std::vector <int> history;

    // last[0] : Last submission time of all
    // last[1~ 26] : Last submission time of problem 'A' ~ 'Z'
    // [0~3] : Four status
    // last  =  Last submission time,
    std::vector <array_4> last;

    // The last submission problem of a certain state.
    array_4 last_submission;

    inline team &operator =(const team &team2) {
        last    = team2.last;
        pass    = team2.pass;
        history = team2.history;
        last_submission = team2.last_submission;
        return *this;
    }

    /// @brief Change the status in SCROLL operation.
    /// Equal to submit a new AC in O(m)
    inline void change(int problem,int time,int fails) {
        pass[0] += time + fails * 20; // Update penalty count.
        auto iter = std::lower_bound(history.begin(),
                                     history.end(),
                                     time);
        history.insert(iter,time); // Update history
    }

    /// @brief Whether the team passed this problem 
    inline bool passP(int problem) const{
        return pass[problem] > 0;
    }

    /// @brief Fail times before AC
    inline int passF(int problem) const{
        if(pass[problem] < 0) throw("");
        return pass[problem] - 1;
    }

    /// @brief Fail times without AC
    inline int failF(int problem) const{
        if(pass[problem] > 0) throw("");
        return pass[problem];
    }

    // pass number count
    inline int passCount() const{
        return history.size();
    }


    // penalty time in all
    inline int penalty() const {
        return pass[0];
    }

    /// @brief Whether this problem can bring new AC 
    inline bool judgeAC(int problem,status _st) const{
        return pass[problem] <= 0 && _st == AC;
    }

    /// @brief Submit problem at time with _st as status 
    inline void sumbit(int problem,int time,status _st) {
        // Update last first
        last[problem][_st] = time;
        last[0][_st] = time;
        last_submission[_st] = problem;
        // If not AC,update submission state
        if(pass[problem] <= 0) { // Have not AC yet
            if(_st == AC) { // Pass this problem
                pass[0] += pass[problem] * (-20) + time;
                pass[problem] = 1 - pass[problem];
                history.push_back(time);
            } else { // Add to the penalty
                --pass[problem];
            }
        }
    }
    /// @brief Initialize last,pass as an array
    /// while history as a stack
    team() {
        last.resize(problemCount + 1);
        pass.resize(problemCount + 1);
        last_submission[AC] = 0;
        last_submission[WA] = 0;
        last_submission[RE] = 0;
        last_submission[TL] = 0;
    }
};
std::vector <team> teamData;    // Real time data of each team
std::vector <team> frozenData;  // Temp team data if frozen


/// @brief Real-time compare function class
struct compare {
    // Custom less operation
    bool operator ()(int ID1,int ID2) const{
        // Whether identical
        if(ID1 == ID2) return false;

        const team &team1 = teamData[ID1];
        const team &team2 = teamData[ID2];

        // Pass count
        if(team1.passCount() != team2.passCount()) {
            return team1.passCount() > team2.passCount();
        }

        // Penalty time in all
        if(team1.penalty() != team2.penalty()) {
            return team1.penalty() < team2.penalty();
        }

        // time from big to small
        for(int i = team1.passCount() - 1 ; i != -1 ; --i) {
            if(team1.history[i] != team2.history[i]) {
                return team1.history[i] < team2.history[i];
            }
        }

        // alphabetic order
        return ID1 < ID2;
    }

};


/// @return Find the teamID of a team (0-base) in O(logn).
///         If not found , it will return -1
inline int getTeamID(const string &Name) {
    int l = 0, r = teamCount, mid,cmp;
    // Iterator style binary search
    while(l != r) { // Search [l,r)
        mid = (l + r) >> 1; 
        cmp = Name.compare(teamName[mid]);
        if(cmp == 2) return mid;
        // Now mid not available
        if(cmp == 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return -1; // Do not exist
}


// Public scoreboard of teamID
// If frozen , it won't change
std::set <int,compare>   scoreboard;
}