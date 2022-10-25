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


///@brief skip reading next string or number.
void skip_string() {
    char _buff = getchar(); // temporary buffer
    while(_buff == ' ' || _buff == '\n'  || _buff == EOF) {
        _buff = getchar();
    }
    while(_buff != ' ' && _buff != '\n'  && _buff != EOF) {
        _buff = getchar();
    }
}


const unsigned INF = 1919810;   // infinity for this program
const unsigned kProblems = 26;  // maximum number of problems


// status : AC = 0,WA = 1,RE = 2,TL = 3,
enum status {AC,WA,RE,TL};


status status_map[128];     // mapping a char into status 
string buffer;              // common buffer for string to read in

std::map<string,int>nameMap;// record team names
bool gameStart  = false;    // whether the game starts
bool gameFreeze = false;    // whether the billboard is frozen
bool gameChange = false;    // whether there is new pass AC
int  duration = 0;          // the duration of the game
int  problem_count = 0;     // total count of problems

// recording rank after FLUSH operation
std::vector <int> flushed_rank;

/// @brief Real time time-data of a team
struct team {
    // last[0] : last submission of all    
    // last[1~ 26] : last submission of problem 'A' ~ 'Z'
    // [4] : Four status
    // last  =  last submission time,
    std::vector <int[4]> last;

    // pass[0]:penalty time in all pass cases
    // pass[1 ~ 26]:penalty time of question
    // pass  =  0 uninitalized
    // pass  <  0 fail for -pass times
    // pass  >  0 successfull pass
    std::vector <int> pass;

    // history submit from small to big in tme
    std::vector <int> history;

    // pass number count
    inline int passCount() const{
        return history.size();
    }
    // penalty time in all
    inline int penalty() const {
        return pass[0];
    }
    /// @brief if this problem can bring new AC 
    inline bool judgeAC(int problem,status _st) {
        return pass[problem] <= 0 && _st == AC;
    }

    /// @brief submit problem at time with _st as status 
    inline void sumbit(int problem,int time,status _st) {
        // update last first
        last[problem][_st] = time;
        last[0][_st] = time;
        
        // if not AC,update submission state
        if(pass[problem] <= 0) { // have not AC yet
            if(_st == AC) { // pass this problem
                pass[problem] = pass[problem] * (-10) + time;
                pass[0] += pass[problem];
                // find the postion for this pass time
                auto iter = std::upper_bound(history.begin(),
                                             history.end(),
                                             pass[problem]);
                history.insert(iter,pass[problem]);
            } else { // add to the penalty
                --pass[problem];
            }
        }
    }
    /// @brief Initialize last,pass as an array
    /// while history as a stack
    team() {
        last.resize(problem_count + 1,{0,0,0,0});
        pass.resize(problem_count + 1,0);
        history.reserve(problem_count);
    }
};
std::vector <team> teamData;// real time data of each team


/// @brief Compare function class
struct compare {
    // custom less operation
    bool operator ()(int ID1,int ID2) const{
        // whether identical
        if(ID1 == ID2) return false;

        const team & team1 = teamData[ID1];
        const team & team2 = teamData[ID2];

        // pass count
        if(team1.passCount() != team2.passCount()) {
            return team1.passCount() < team2.passCount();
        }

        // penalty time in all
        if(team1.penalty() != team2.penalty())
            return team1.penalty() < team2.penalty();
        
        // penalty time from big to small
        for(int i = team1.passCount() - 1 ; i != -1 ; --i) {
            if(team1.history[i] != team2.history[i]) {
                return team1.history[i] < team2.history[i];
            }
        }

        // alphabetic order
        return ID1 < ID2;
    }

};
std::set <int,compare> billboard;// real time billboard


/// @return the teamID of a team
inline int getTeamID(const string &teamName) {
    return nameMap[teamName];
}

/// @brief Things to do before starting the game
void prework() {
    int rank = 0;// alphabetic rank of team
    for(auto it : nameMap) {
        it.second = rank++;
    }

    // reserve enough space for flush_rank
    flushed_rank.reserve(rank);

    status_map['A'] = AC;
    status_map['W'] = WA;
    status_map['R'] = RE;
    status_map['T'] = TL; 
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
    int &iter = nameMap[teamName];
    if(iter != 0) {
        // Fail to insert such a name
        // so there exists an identical name
        write << "[Error]Add failed: duplicated team name.\n";
    } else { 
        // Successful insertion
        iter = 1;
        write << "[Info]Add successfully.\n";
    }
}
/// @brief START operation
void start() {
    skip_string();  // DURATION
    if(gameStart) { // Error occurred,so skip reading everything
        skip_string();
        skip_string();
        skip_string();
        write << "[Error]Start failed: competition has started.\n";
        return;
    }

    gameStart = true;
    read >> duration;
    skip_string(); // PROBLEM
    read >> problem_count;
    prework();

    
}

/// @brief SUBMIT operation
void submit() {
    char problem; // the problem to solve
    char _status; // statue char
    int _time;    // time of submission

    read >> problem;
    problem ^= 64; // 'A'~'Z' -> 1 ~ 26;

    skip_string(); // BY
    
    #define teamName buffer
    read >> teamName;
    int teamID = getTeamID(teamName);
    team & team1 = teamData[teamID]; // current team

    skip_string(); // WITH 

    read >> _status;

    skip_string();  // remainder of the status string
    skip_string();  // AT

    read >> _time;

    // if there will be new AC
    bool flag = team1.judgeAC(problem,status_map[_status]);
    if(flag) billboard.erase(teamID);
    team1.sumbit(problem,_time,status_map[_status]);
    if(flag) billboard.insert(teamID);
    if(gameFreeze) {

    } else {
        if(flag) gameChange = true;
    }
}

/// @brief FLUSH operation in O(n)
void flush() {
    // the game doesn't make a difference
    if(!gameChange) return;
    flushed_rank.clear();
    for(auto iter : billboard) {
        flushed_rank.push_back(iter);
    }
    write << "[Info]Flush scoreboard.\n";
    gameChange = false;
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
            flush();
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