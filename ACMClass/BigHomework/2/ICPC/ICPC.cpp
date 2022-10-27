#include<bits/stdc++.h>
//using namespace std;
//#define int lont long

namespace ICPC{

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

const unsigned kProblems = 26;  // Maximum number of problems


string buffer;              // Common buffer for string to read in


bool gameStart  = false;    // Whether the game starts
bool gameFreeze = false;    // Whether the scoreboard is frozen
bool gameChange = false;    // Whether there is new pass AC before freezing
int  duration      = 0;     // The duration of the game
int  problem_count = 0;     // Total count of problems


// Set to judge if a name has existed.
std::set <string> nameSet;
// TeamNames in alphabetic order.
std::vector <string> teamName; 
// Recording given ID's rank
// Value is 1-base , namely first = 1
std::vector <int> flushedRank;

// The submissions after frozen of each team
// submissions[i][j] problem:i submission from ID:j
std::vector <std::vector<int>> submissions;

// status : AC = 0,WA = 1,RE = 2,TL = 3,
enum status {AC,WA,RE,TL};
status status_map[96];     // Mapping a char into a status 


/// @brief Real time time-data of a team
struct team {
    // special vector
    struct array_4 {
        int data[4];
        int & operator[](size_t index_pos) {
            return data[index_pos];
        }
        int operator[](size_t index_pos) const{
            return data[index_pos];
        }
    };

    // last[0] : last submission of all    
    // last[1~ 26] : last submission of problem 'A' ~ 'Z'
    // [0~3] : Four status
    // last  =  last submission time,
    std::vector <array_4> last;

    // pass[0]:penalty time in all pass cases
    // pass[1 ~ 26]:penalty time of question
    // pass  =  0 uninitalized
    // pass  <  0 fail for -pass times
    // pass  >  0 successfull pass
    std::vector <int> pass;


    // history submit time from small to big
    std::vector <int> history;

    team &operator =(const team &team2) {
        last = team2.last;
        pass = team2.pass;
        history = team2.history;
        return *this;
    }

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
                history.push_back(time);
            } else { // add to the penalty
                --pass[problem];
            }
        }
    }
    /// @brief Initialize last,pass as an array
    /// while history as a stack
    team() {
        last.resize(problem_count + 1);
        pass.resize(problem_count + 1);  
    }
};
std::vector <team> teamData;    // Real time data of each team
std::vector <team> frozenData;  // Temp team data if frozen

/// @brief Compare function class
struct compare {

    // Custom less operation
    bool operator ()(int ID1,int ID2) const{
        // Whether identical
        if(ID1 == ID2) return false;

        const team &team1 = teamData[ID1];
        const team &team2 = teamData[ID2];

        // Pass count
        if(team1.passCount() != team2.passCount()) {
            return team1.passCount() < team2.passCount();
        }

        // Penalty time in all
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
// Public scoreboard of teamID
// If frozen , it won't change
std::set <int,compare> scoreboard;



/// @return Find the teamID of a team (0-base) in O(logn)
inline int getTeamID(const string &Name) {
    int l = 0, r = teamName.size(), mid,cmp;
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


/// @brief Things to do before starting the game,
/// Initialize frozenRank, flushedRank, teamName
/// and scoreboard in O(nlogn)
void prework() {
    // Reserve space for teamData
    // Use it like an array 
    teamData.resize(nameSet.size());


    // Reserve space for flushedRank
    // Use it like an array
    flushedRank.resize(nameSet.size());
    // Initialize scoreboard and flushedRank
    for(int i = 0 ; i < (int)nameSet.size() ; ++i) {
        scoreboard.insert(i);
        flushedRank[i] = i+1;
    }


    // Reserve space for nameSet
    teamName.reserve(nameSet.size());
    // Initialize teamName
    for(auto &&it : nameSet) {
        teamName.push_back(it);
    }


    // Initialize status_map
    status_map['A'] = AC;
    status_map['W'] = WA;
    status_map['R'] = RE;
    status_map['T'] = TL;

    //Initialize submissions.
    submissions.resize(problem_count+1);
    for(int i = 1 ; i <= problem_count ; ++i)
        submissions[i].resize(nameSet.size());
}

/// @brief ADDTEAM operation in O(logn)
void addTeam() {
    if(gameStart) { // Error occurred, so skip reading
        skip_string();
        write << "[Error]Add failed: competition has started.\n";
        return;
    }

    #define Name buffer
    read >> Name;

    if(nameSet.insert(Name).second == false) {
        // Fail to insert such a name
        // so there exists an identical name
        write << "[Error]Add failed: duplicated team name.\n";
    } else { 
        // Successful insertion
        write << "[Info]Add successfully.\n";
    }

    #undef Name
}

/// @brief START operation in O(nlogn)
void start() {
    skip_string();  // DURATION

    if(gameStart) { // Error occurred,so skip reading everything
        skip_string(); // duration
        skip_string(); // PROBLEM
        skip_string(); // problem_count
        write << "[Error]Start failed: competition has started.\n";
        return;
    }
    gameStart = true;
    read >> duration;

    skip_string();   // PROBLEM

    read >> problem_count;

    prework(); // Doing something beforehand
}

/// @brief SUBMIT operation in O(logn)
void submit() {
    char problem; // The problem to solve
    char _status; // Status char
    int  _time;   // Time of submission

    read >> problem;
    problem ^= 64; // 'A'~'Z' -> 1 ~ 26;

    skip_string(); // BY

    #define Name buffer
    read >> Name;
    int ID = getTeamID(Name);
    team & team1 = teamData[ID]; // Current team

    skip_string(); // WITH

    read >> _status;

    skip_string();  // Remainder of the status string
    skip_string();  // AT

    read >> _time;

    // Note down submission count
    if(gameFreeze && frozenData[ID].pass[problem] != false) {
        ++submissions[status_map[int(_status)]][ID];
    }

    // Whether there will be new AC
    bool flag = team1.judgeAC(problem,status_map[int(_status)]);
    // Nothing to update.
    if(flag == false || gameFreeze == true) {
        team1.sumbit(problem,_time,status_map[int(_status)]);
    } else { // Now not freeze + new AC
        // The scoreboard won't change after freezing
        scoreboard.erase(ID);
        team1.sumbit(problem,_time,status_map[int(_status)]);        
        scoreboard.insert(ID);
        gameChange = true;
    }
    #undef Name
}

/// @brief FLUSH operation in O(n)
void flush() {
    // "The game doesn't make a difference" case.
    if(gameChange == false) return;
    
    // Now update flushed rank
    write << "[Info]Flush scoreboard.\n";
    gameChange = false;
    // Update flushed rank
    int rank = 0;
    for(auto iter : scoreboard) {
        flushedRank[iter] = ++rank;
    }
}

/// @brief FREEZE operation in O(n)
void freeze() {
    if(gameFreeze) {
        write << "[Error]Freeze failed: scoreboard has been frozen.\n";
        return;
    }
    gameFreeze = true;
    write << "[Info]Freeze scoreboard.\n";
    // update frozon rank
    frozenData = teamData;
}


/// @brief SCROLL operation in O(nlogn)
void scroll() {
    teamData.swap(frozenData); // go back to frozen state
    gameFreeze = false; // Defreeze
    // The first untested index of a teamName
    std::vector <int> first_index(teamName.size(),1);
    int rank = 0;
    for(auto ID : scoreboard) {
        ++rank;
        write << teamName[ID] << ' '
              << rank         << ' '
              << teamData[ID].passCount() << ' '
              << teamData[ID].penalty()   << ' ';
        for(int i = 1 ; i <= problem_count ; ++i) {
            if(teamData[ID].pass[i] > 0)
                write << '+';
            write << teamData[ID].pass[i] << ' ';            
        }
    }


    while(!scoreboard.empty()) {
        auto iter = --scoreboard.end(); 
        int ID = *iter;
        if(teamData[ID].penalty() == frozenData[ID].penalty()) {
            scoreboard.erase(iter);
            continue;
        }
        // Use i as problem ID
        for(int i = first_index[ID] ; i <= problem_count ; ++i) {
            if(teamData[ID].pass[i] <= 0 &&
             frozenData[ID].pass[i] >  0) {
                // Now this might affect ranking
                scoreboard.erase(iter);
                iter = scoreboard.insert(ID).first;
                ++iter;
                if(iter == scoreboard.end()) continue;
                write << teamName[ID]    << ' ' 
                      << teamName[*iter] << ' '
                      << teamData[ID].passCount() << ' '
                      << teamData[ID].penalty()   << '\n';
                first_index[ID] = i + 1;
                break; 
            }
        }
    }


}

/// @brief QUERY_SUBMISSION O(logn)
inline void query_ranking() {
    #define Name buffer
    read >> Name;
    int ID = getTeamID(Name);
    if(ID == -1) {
        // Not found
        write << "[Error]Query ranking failed: cannot find the team.\n";
    } else {
        write << "[Info]Complete query ranking.\n";
        if(gameFreeze) {
            write << "[Warning]Scoreboard is frozen. ";
            write << "The ranking may be inaccurate until it were scrolled.\n";
        }
        write << flushedRank[ID];
    }
    #undef Name
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
            freeze();
            break;
        case 'C': // SCROLL
            scroll();
            break;
        case 'N': // END
            return false;
        default:
            if(command[6] == 'R') { // QUERY_RANKING
                query_ranking();
            }
            else { // QUERY_SUBMISSION

            }
    }
    return true;
    #undef command
}




}



signed main() {
    while(ICPC::readCommand());
    return 0;
}