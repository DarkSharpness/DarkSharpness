#include<bits/stdc++.h>
//using namespace std;
//#define int lont long

namespace ICPC{

/// @brief test whether it is the end of string
inline bool isEnd(char _ch) {
    return _ch == ' ' || _ch == '\n'  ||
           _ch == EOF || _ch == '\0';
}

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
}read; // A substitue for cin

class outstream {
    public:
    char buff[100]; // standard buffer for output
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
        if(!num) { // special case of 0
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
 * @brief Use the last char to record the size.
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
    bool operator <(const string & str) const{
        size_cptr ptr1 = reinterpret_cast <size_cptr> (this);    
        size_cptr ptr2 = reinterpret_cast <size_cptr> (&str);
        for(int i = 2 ; i >= 0 ; --i) {
            if(ptr1[i] < ptr2[i]) return true;
            if(ptr1[i] > ptr2[i]) return false;
        }
        return false;//the same
    }
    /// @brief Custom read in for string
    friend instream & operator >>(instream & read,string &str) {
        memset(str.c,0,sizeof(str.c)); // clear previous data.
        char _buff = getchar(); // temporary buffer
        while(_buff == ' ' || _buff == '\n'  || _buff == EOF) {
            _buff = getchar();
        }
        char *top = str.c + 24; // current top pointer
        while(_buff != ' ' && _buff != '\n'  && _buff != EOF) {
            *(--top) = _buff;
            _buff = getchar();
        }
        str.c[0] = str.c + 24 - top;
        return read;
    }
    /// @brief Custom print out for string
    friend outstream & operator <<(outstream & write,const string &str) {
        const char *top = str.c + 24; // current top pointer
        while(*top != '\0') {
            putchar(*(--top));
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



const unsigned INF = 1919810;   // infinity for this program
const unsigned kProblems = 26;  // maximum number of problems


// status : AC = 0,WA = 0,RE = 0,TL = 0,
enum status {AC,WA,RE,TL};

// the data of each team
struct team {

    // last[1~ 26] : last submission of problem 'A' ~ 'Z'
    // last[0] : last submission of all    
    int last[kProblems+1][4];
    int penalty;    // penalty time

    inline void sumbit(int problem,int time,status _st) {
        last[problem][_st] = time;
        last[0][_st] = time;
        if(penalty <= 0) { // have no AC yet
            if(_st == AC) { // pass this problem
                penalty = penalty * (-10) + time;
            } else { // add to the penalty
                --penalty;
            }
        }
    }

};

///@brief Skip reading next string or number.
void skip_string() {
    char _buff = getchar(); // temporary buffer
    while(_buff == ' ' || _buff == '\n'  || _buff == EOF) {
        _buff = getchar();
    }
    while(_buff != ' ' && _buff != '\n'  && _buff != EOF) {
        _buff = getchar();
    }
}

string buffer;              // common buffer for read in

std::map<string,int>nameMap;// record team names and its alphabetic rank
bool gameStart  = false;    // whether the game starts
bool gameFreeze = false;    // whether the billboard is frozen
int  duration = 0;          // the duration of the game
int  problem_count = 0;     // total of problems
std::vector <team> gameData;// data of each team

void submit()


/// @brief Things to do before starting the game
void prework() {
    int rank = 0;// alphabetic rank of team
    for(auto it : nameMap) {
        it.second = rank++;
    }
}


/// @brief ADDTEAM operation
void addTeam() {
    if(gameStart) { // Error occurred, so skip reading
        skip_string();
        write << "[Error]Add failed: competition has started.\n";
        return;
    }

    #define teamName buffer
    read >> teamName;
    auto iter = nameMap.find(teamName);
    if(iter == nameMap.end()) {
        // Fail to insert such a name
        // so there exists an identical name
        write << "[Error]Add failed: duplicated team name.\n";
    } else { // Successful insertion
        (*iter).second = 1;
        write << "[Info]Add successfully.\n";
    }
}
/// @brief START operation
void start() {
    skip_string();  // This string is useless!
    if(gameStart) { // Error occurred,so skip reading everything
        skip_string();
        skip_string();
        skip_string();
        write << "[Error]Start failed: competition has started.\n";
        return;
    }

    read >> duration;
    skip_string(); // This string is useless!
    read >> problem_count;
    prework();

}

void submit() {
    
}


/// @brief read in a single command
bool readCommand() {
    #define command buffer
    read >> command;
    switch(command[1]) {
        case 'D': // ADDTEAM
            addTeam();
            break;
        case 'T': // START
            start();
            break;
        case 'U': // SUBMIT
            submit();
            break;
        case 'L': // FLUSH

            break;
        case 'R': // FREEZE
            break;
        case 'C': // SCROLL

            break;

        case 'N': // END
            return false;
        default:
            if(command[6] == 'R') { // QUERY_RANKING

            }
            else { // QUERY_SUBMISSION

            }
    }
    return true;
}



}



signed main() {
    while(ICPC::readCommand());
    return 0;
}