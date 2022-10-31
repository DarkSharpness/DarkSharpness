#include "ICPC.h"


namespace ICPC{

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


    // Reserve space for teamData
    // Use it like an array 
    teamData.resize(teamCount);


    // Reserve space for flushedRank
    // Use it like an array
    flushedRank.reserve(teamCount);
    // Initialize scoreboard and flushedRank
    for(int i = 0 ; i < teamCount ; ++i) {
        scoreboard.insert(i);
        flushedRank.push_back(i+1);
    }


    // Reserve space for nameSet
    teamName.reserve(teamCount);
    // Initialize teamName
    for(auto &&it : nameSet) {
        teamName.push_back(it);
    }


    // Initialize status_map
    status_map['A'] = AC;
    status_map['W'] = WA;
    status_map['R'] = RE;
    status_map['T'] = TL;

    // Initialize submission
    submissions.resize(problemCount+1);
    for(int i = 1 ; i <= problemCount ; ++i) {
        submissions.resize(teamCount);
    }
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
    team & team1 = teamData[ID]; // Current team

    skip_string(); // WITH

    read >> _status;
    // The status now.
    status _st = status_map[int(_status)];

    skip_string();  // Remainder of the status string
    skip_string();  // AT

    read >> _time;

    if(gameFreeze == true) { // Game freeze state.
        team1.sumbit(problem,_time,_st);
        // If frozon problem(not passed before frozen)
        if(frozenData[ID].passP(problem) == false) {
            submissions[problem][ID].submit();
            if(_st == AC) {submissions[problem][ID].addAC(_time);}
        }
    } else { // Game not freeze state.
        if(team1.judgeAC(problem,_st) == false) {
            // No new AC.
            team1.sumbit(problem,_time,_st);
        } else {
            // With new AC,
            // so update scoreboard
            scoreboard.erase(ID);
            team1.sumbit(problem,_time,_st);
            scoreboard.insert(ID);
            gameChange = true;
        }
    }

    #undef Name
}

/// @brief FLUSH operation in O(n)
void flush() {
    if(gameChange == false) {
        // "The game doesn't make a difference" case.
        return;
    }

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
    const team &team1 = teamData[ID];

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
    int _time = 0;
    if(STATUS[7] == 'A' && STATUS[8] == 'L') {
        // STATUS  ALL CASE
        for(int i = 0 ; i < 4 ; ++i) {
            if(team1.last[problem][i] > _time) {
                _time = team1.last[problem][i];
                _st   = status(i);
            } else {} // Nothing
        }
        if(problem == 0) {
            problem = team1.last_submission[_st];
        } else {} // Nothing
    } else {
        // AC,WA,RE,TLE CASE
        _time = team1.last[problem][_st];
        if(problem == 0) { // Find the problem index
            problem = team1.last_submission[_st];
        } else {}; // Nothing
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
    freopen()
    freopen("ans.out","w",stdout);
    while(ICPC::readCommand());
    ICPC::write << "[Info]Competition ends.\n";
    return 0;
}