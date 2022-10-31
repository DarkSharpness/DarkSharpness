#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
namespace ICPC {

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
    /// @brief Submit after freezing
    inline void submit() {
        ++submission_times;
    }
    /// @brief Add AC_data after freezing.
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

/// @brief Special array for status
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

/// @brief Store latest information.
class historyInfo {
    private:
    // [i][j]: Last submission time of problem i,status j.
    std::vector <array_4> lastTime;
    // [i]: Last status of problem i.
    std::vector <status>  lastStatus;
    // [i]: Last problem of status i.
    array_4               lastProblem;
    #define last_submission_problem lastTime[0][0]
    #define last_submission_status  lastStatus[0]

    public:
    /// @brief Update history information.
    inline void update(int problem,int time,status _st) {
        lastTime[problem][_st]  = time;
        lastProblem[_st]        = problem;
        lastStatus[problem]     = _st;
        last_submission_problem = problem;
        last_submission_status  = _st;
    }

    /// @brief Get the status and problem.
    inline int getALLALL(int &problem,status &_st) {
        problem = last_submission_problem;
        _st     = last_submission_status;
        if(problem == 0) {
            return 0; // Problem not found
        }
        return lastTime[problem][_st];
    }
    /// @brief Get the status.
    inline int getPROBLEMALL(int problem,status &_st) {
        _st = lastStatus[problem];
        return lastTime[problem][_st];
    }
    /// @brief Get the problem
    inline int getALLSTATUS(int &problem,status _st) {
        problem = lastProblem[_st];
        if(problem == 0) {
            return 0;// Problem not found
        }
        return lastTime[problem][_st];
    }
    inline int getPROBLEMSTATUS(int problem,status _st) {
        return lastTime[problem][_st];
    }

    #undef last_submission_problem
    #undef last_submission_status
    historyInfo() {
        lastTime.  resize(problemCount + 1);
        lastStatus.resize(problemCount + 1);
    }
};
/// History-data of a team
std::vector <historyInfo> historyData;

/// @brief Time-data of a team
class team {
    private:

    // pass[0]:Penalty time in all pass cases
    // pass[1 ~ 26]:Submission count before passed.
    // pass  =  0 uninitalized
    // pass  <  0 fail for -pass times
    // pass  >  0 successfull pass
    std::vector <int> pass;
    
    public:

    // History AC submit time from small to big
    std::vector <int> history;

    inline team &operator =(const team &team2) {
        pass        = team2.pass;
        history     = team2.history;
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
        pass.resize(problemCount + 1);
    }
};
std::vector <team> teamData;    // Real time data of each team
std::vector <team> frozenData;  // Temp team data if frozen


/// @brief Real-time compare function class
class compare {
    public:
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

namespace ICPC{

inline void submit(int ID,int problem,int time,status _st) {
    teamData[ID].sumbit(problem,time,_st);
    historyData[ID].update(problem,time,_st);
}

/// @brief Print out frozen scoreboard
inline void printFreeze() {
    scoreboard.clear();
    for(int i = 0 ; i < teamCount ; ++i) {scoreboard.insert(i);}
    int rank = 0;
    for(auto ID : scoreboard) {
        const team & team1 = teamData[ID];
        write << teamName[ID]      << ' '
              << ++rank            << ' '
              << team1.passCount() << ' '
              << team1.penalty()   << ' ';
        for(int i = 1 ; i <= problemCount ; ++i) {
            if(team1.passP(i) == false) {
                if(submissions[i][ID].submission_times != 0) {
                // Freezing state.
                write << team1.failF(i) << '/'
                      << submissions[i][ID].submission_times
                      << ' ';
                } else { 
                    // Not freezing + not passed
                    if(team1.failF(i) == 0) {
                        write << ". ";
                    } else {write << team1.failF(i) << ' ';}
                }
            } else {
                write << '+';
                if(team1.passF(i) > 0) {
                    write << team1.passF(i);
                }
                write << ' ';
            }
        }
        write << '\n';
    }

}

/// @brief Print out updated scoreboard
inline void printUpdate() {
    scoreboard.clear();
    for(int i = 0 ; i < teamCount ; ++i) {scoreboard.insert(i);}
    int rank = 0;
    for(auto ID : scoreboard) {
        const team & team1 = teamData[ID];
        write << teamName[ID]      << ' '
              << ++rank            << ' '
              << team1.passCount() << ' '
              << team1.penalty()   << ' ';
        for(int i = 1 ; i <= problemCount ; ++i) {
            if(team1.passP(i) == false) {
                // Not passed
                
                if(team1.failF(i) == 0) {
                    write << ". ";
                } else {write << team1.failF(i) << ' ';}
            } else { // Passed
                write << '+';
                if(team1.passF(i) > 0) {
                    write << team1.passF(i);
                } else {} // Nothing
                write << ' ';
            }
        }
        write << '\n';
    }
}

/// @brief Things to do before starting the game,
/// Initialize frozenRank, flushedRank, teamName
/// and scoreboard in O(nlogn)
void prework() {
    // update teamCount
    teamCount = nameSet.size();

    // Reserve space for teamData.
    // Use it like an array.
    teamData.resize(teamCount);

    // Reserve space for flushedRank.
    // Use it like an array.
    flushedRank.reserve(teamCount);
    // Initialize scoreboard and flushedRank.
    for(int i = 0 ; i < teamCount ; ++i) {
        scoreboard.insert(i);
        flushedRank.push_back(i+1);
    }

    // Reserve space for nameSet.
    teamName.reserve(teamCount);
    // Initialize teamName
    for(auto &&it : nameSet) {
        teamName.push_back(it);
    }

    // Initialize status_map.
    status_map['A'] = AC;
    status_map['W'] = WA;
    status_map['R'] = RE;
    status_map['T'] = TL;

    // Initialize submission
    submissions.resize(problemCount+1);
    for(int i = 1 ; i <= problemCount ; ++i) {
        submissions.resize(teamCount);
    }

    // Initialize historyData.
    // Just use it like an array.
    historyData.resize(teamCount);
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
        skip_string(); // problemCount
        write << "[Error]Start failed: competition has started.\n";
        return;
    }

    write << "[Info]Competition starts.\n";
    gameStart = true;
    read >> duration;

    skip_string();   // PROBLEM

    read >> problemCount;

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

    skip_string(); // WITH

    read >> _status;
    // The status now.
    status _st = status_map[int(_status)];

    skip_string();  // Remainder of the status string
    skip_string();  // AT

    read >> _time;

    if(gameFreeze == true) { // Game freeze state.
        submit(ID,(int)problem,_time,_st);
        // If frozon problem(not passed before frozen)
        if(frozenData[ID].passP(problem) == false) {
            submissions[problem][ID].submit();
            if(_st == AC) {submissions[problem][ID].addAC(_time);}
        }
    } else { // Game not freeze state.
        if(teamData[ID].judgeAC(problem,_st) == false) {
            // No new AC.
            submit(ID,(int)problem,_time,_st);
        } else {
            // With new AC,
            // so update scoreboard
            scoreboard.erase(ID);
            submit(ID,(int)problem,_time,_st);
            scoreboard.insert(ID);
            gameChange = true;
        }
    }

    #undef Name
}

/// @brief FLUSH operation in O(n)
void flush() {
    write << "[Info]Flush scoreboard.\n";

    if(gameChange == false) {
        // "The game doesn't make a difference" case.
        return;
    }

    // Now update flushed rank
    gameChange = false;
    // Update flushed rank
    int rank = 0;
    for(auto iter : scoreboard) {
        flushedRank[iter] = ++rank;
    }
}

/// @brief FREEZE operation in O(n)
void freeze() {
    if(gameFreeze == true) {
        // Duplicated freeze operation.
        write << "[Error]Freeze failed: scoreboard has been frozen.\n";
        return;
    }

    
    for(int i = 1 ; i <= problemCount ; ++i) {
        submissions[i].clear();
        submissions[i].resize(teamCount);
    }

    // Start freezing.
    gameFreeze = true;
    write << "[Info]Freeze scoreboard.\n";

    // Update frozon rank.
    frozenData = teamData;
}


/// @brief SCROLL operation in O(nlogn)
void scroll() {
    if(gameFreeze == false) {
        write << "[Error]Scroll failed: scoreboard has not been frozen.\n";
        return;
    }

    write << "[Info]Scroll scoreboard.\n";
    gameFreeze = false; // Defreeze

    // Go back to pre-frozen state in O(1);
    teamData.swap(frozenData);

    printFreeze();
    // The first untested index of a teamName
    static std::vector <int> first_index;
    // Initialize first_index
    first_index.assign(teamName.size(),1);

    while(scoreboard.size() != 1) {
        auto iter = --scoreboard.end();
        int ID = *iter;
        // End of iter.
        if(teamData[ID].passCount() == frozenData[ID].passCount()) {
            scoreboard.erase(iter);
            continue;
        }
        for(int i = first_index[ID]; i <= problemCount ; ++i) {
            if(teamData[ID].passP(i) == false &&
             frozenData[ID].passP(i) == true) {
                teamData[ID].change(i,
                                    submissions[i][ID].first_AC_time,
                                    frozenData[ID].passF(i));
                --iter;
                // If the rank doesn't changing
                if(compare()(*iter,ID)) {continue;}
                // Now the rank does change
                ++iter;
                scoreboard.erase(iter);
                iter = ++scoreboard.insert(ID).first;
                write << teamName[ID]             << ' '
                      << teamName[*iter]          << ' '
                      << teamData[ID].passCount() << ' '
                      << teamData[ID].penalty()   << '\n';
                first_index[ID] = i + 1;
                break;
            }
        }
    }

    // Go back to updated state in O(1);
    teamData.swap(frozenData);
    printUpdate();

    // Update scoreboard
    int rank = 0;
    for(auto iter : scoreboard) {
        flushedRank[iter] = ++rank;
    }
    gameChange = false;
}

/// @brief QUERY_RANKING O(logn)
void query_ranking() {
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
        write << Name << " NOW AT RANKING "<< flushedRank[ID] << '\n';
    }
    #undef Name
}

/// @brief QUERY_SUBMISSION O(logn)
void query_submission() {
    #define Name buffer
    read >> Name;
    int ID = getTeamID(Name);
    if(ID == -1) {
        skip_line();
        write << "[Error]Query submission failed: cannot find the team.\n";
        return;
    }

    // team exists
    write << "[Info]Complete query submission.\n";

    skip_string(); // WHERE

    #define Problem buffer2
    read >> Problem;
    int problem = Problem[8] ^ 64; // A ~ Z -> 1 ~ 26;
    if(Problem[9] != '\0') {
        // ALL case
        problem = 0;
    }

    skip_string(); // AND

    #define STATUS buffer2
    read >> STATUS;
    status _st = status_map[(int)STATUS[7]];
    int _time;
    if(STATUS[7] == 'A' && STATUS[8] == 'L') {
        // STATUS  ALL CASE
        if(problem == 0) {
            _time = historyData[ID].getALLALL(problem,_st);
        } else {
            _time = historyData[ID].getPROBLEMALL(problem,_st);
        }
    } else {
        if(problem == 0) {
            _time = historyData[ID].getALLSTATUS(problem,_st);
        } else {
            _time = historyData[ID].getPROBLEMSTATUS(problem,_st);
        } // Nothing
    }
    if(_time == 0) {
        write << "Cannot find any submission.\n"; 
    } else {
        write << Name               << ' '
              << char(problem ^ 64) << ' '
              << status_string[_st] << ' '
              << _time              << '\n';
    }
    #undef Name
    #undef Problem
    #undef STATUS
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
            if(command[6] == '\0') { // SUBMIT
                submit();
            } else if(command[6] == 'R') { // QUERY_RANKING
                query_ranking();
            }else { // QUERY_SUBMISSION
                query_submission();
            }
    }
    return true;
    #undef command
}

} // END of ICPC


signed main() {
    //freopen("ICPC/data/10.in","r",stdin);
    //freopen("ans.out","w",stdout);
    while(ICPC::readCommand());
    ICPC::write << "[Info]Competition ends.\n";
    return 0;
}