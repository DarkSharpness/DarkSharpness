// The main header file
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>


// Options Sign
const int kAdd = 1;
const int kStart = 2;
const int kSub = 3;
const int kFlush = 4;
const int kFreeze = 5;
const int kScroll = 6;
const int kQrank = 7;
const int kQsub = 8;
const int kEnd = 0;

// The messages used when adding teams
const std::string kAddTeamSuc = "[Info]Add successfully.";
const std::string kAddTeamAfterStarted = "[Error]Add failed: competition has started.";
const std::string kAddTeamDuplicated = "[Error]Add failed: duplicated team name.";

// The messages used when starting the competition
const std::string kStartSuc = "[Info]Competition starts.";
const std::string kStartAlready = "[Error]Start failed: competition has started.";

// The messages used when flushing
const std::string kFlushSuc = "[Info]Flush scoreboard.";

// The messages used when freezing
const std::string kFreezeSuc = "[Info]Freeze scoreboard.";
const std::string kFreezeFail = "[Error]Freeze failed: scoreboard has been frozen.";

// The messages used when scrolling
const std::string kScrollSuc = "[Info]Scroll scoreboard.";
const std::string kScrollFail = "[Error]Scroll failed: scoreboard has not been frozen.";

// The messages used when querying ranking
const std::string kQrankSuc = "[Info]Complete query ranking.";
const std::string kQrankFail = "[Error]Query ranking failed: cannot find the team.";
const std::string kQrankWarn = "[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled.";

// The messages used when querying submission
const std::string kQsubSuc = "[Info]Complete query submission.";
const std::string kQsubNoSub = "Cannot find any submission.";
const std::string kQsubNoTeam = "[Error]Query submission failed: cannot find the team.";

// The messages used when ending the competition
const std::string kEndCompetition = "[Info]Competition ends.";

// The submit status
const int kAC = 0;
const int kWA = 1;
const int kRE = 2;
const int kTLE = 3;
const int kALL = 4;
const std::string kSubmitStatus[] = {"Accepted", "Wrong_Answer", "Runtime_Error", "Time_Limit_Exceed", "ALL"};

#ifndef ICPC_DATA_H
#define ICPC_DATA_H


const int MAXM = 26;

class Submission {
  public:
    int tid, pid, status, tim, submitid;

  public:
    Submission() {}
    Submission(const Submission &x) : tid(x.tid), pid(x.pid), status(x.status), tim(x.tim), submitid(x.submitid) {}
    Submission(int tid, int pid, int status, int tim, int submitid)
        : tid(tid), pid(pid), status(status), tim(tim), submitid(submitid) {}
    bool operator<(const Submission &x) const;
};

class SubmitData {
  public:
    int ac_cnt, submit_tot;
    int submit_cnt[MAXM], submit_cnt_bfac[MAXM];
    int ac_tim[MAXM];
    Submission las_sub[MAXM][4];

  public:
    SubmitData();
    SubmitData(const SubmitData &x);
    void clear();
};

class TeamData {
  public:
    std::string team_name;
    int rank, penalty;
    
  private:
    int tid;
    std::vector<int> ac_tim_sort;
    SubmitData sub, subf;


  public:
    TeamData() { penalty = 0; }
    TeamData(std::string team_name, int tid) : team_name(team_name), tid(tid), penalty(0) {}

    inline bool aced_problem(int pid) { return sub.ac_tim[pid] || subf.ac_tim[pid]; }
    inline bool frozen() { return subf.submit_tot; }
    inline bool frozen(int pid) { return subf.submit_cnt[pid]; }

    bool operator<(const TeamData &x) const;

    Submission last_submit(int pid, int st) { return std::max(sub.las_sub[pid][st], subf.las_sub[pid][st]); }
    
    void submit(const Submission &x);
    void submitf(const Submission &x);
    void output_info(const int now_rank);
    void output_data(const int problem_cnt);
    void output_data_freezed(const int problem_cnt);
    void output_data_replace(const std::string &replaced_team);
    void unfreeze(const int pid);
};

#endif





bool Submission::operator<(const Submission &x) const {
    if (tim != x.tim)
        return tim < x.tim;
    return submitid < x.submitid;
}

SubmitData::SubmitData() {
    ac_cnt = 0;
    for (int i = 0; i < MAXM; i++) {
        submit_cnt[i] = 0;
        submit_cnt_bfac[i] = 0;
        ac_tim[i] = 0;
        for (int j = 0; j < 4; j++)
            las_sub[i][j] = {0, 0, 0, 0, 0};
    }
}
SubmitData::SubmitData(const SubmitData &x) {
    ac_cnt = x.ac_cnt;
    for (int i = 0; i < MAXM; i++) {
        submit_cnt[i] = x.submit_cnt[i];
        submit_cnt_bfac[i] = x.submit_cnt_bfac[i];
        ac_tim[i] = x.ac_tim[i];
        for (int j = 0; j < 4; j++)
            las_sub[i][j] = x.las_sub[i][j];
    }
}
void SubmitData::clear() {
    ac_cnt = 0;
    for (int i = 0; i < MAXM; i++) {
        submit_cnt[i] = 0;
        submit_cnt_bfac[i] = 0;
        ac_tim[i] = 0;
        for (int j = 0; j < 4; j++)
            las_sub[i][j] = {0, 0, 0, 0, 0};
    }
}

void TeamData::submit(const Submission &x) {
    sub.submit_cnt[x.pid]++;
    sub.las_sub[x.pid][x.status] = x;
    if (x.status == kAC && !aced_problem(x.pid)) {
        sub.ac_cnt++;
        sub.ac_tim[x.pid] = x.tim;
        ac_tim_sort.push_back(x.tim);
        penalty += 20 * sub.submit_cnt_bfac[x.pid] + x.tim;
    } else if (x.status != kAC && !aced_problem(x.pid)) {
        sub.submit_cnt_bfac[x.pid]++;
    }
    return;
}
void TeamData::submitf(const Submission &x) {
    subf.submit_tot++;
    subf.submit_cnt[x.pid]++;
    subf.las_sub[x.pid][x.status] = x;
    if (x.status == kAC && !aced_problem(x.pid)) {
        subf.ac_cnt++;
        subf.ac_tim[x.pid] = x.tim;
    } else if (x.status != kAC && !aced_problem(x.pid)) {
        subf.submit_cnt_bfac[x.pid]++;
    }
    return;
}
void TeamData::output_info(const int now_rank) {
    std::cout << team_name << " " << now_rank << " " << sub.ac_cnt << " " << penalty << " ";
}
void TeamData::output_data(const int problem_cnt) {
    for (int j = 0; j < problem_cnt; j++) {
        if (sub.ac_tim[j]) {
            if (sub.submit_cnt_bfac[j])
                std::cout << "+" << sub.submit_cnt_bfac[j];
            else
                std::cout << "+";
        } else {
            if (sub.submit_cnt[j])
                std::cout << "-" << sub.submit_cnt[j];
            else
                std::cout << ".";
        }
        if (j != problem_cnt - 1)
            std::cout << " ";
    }
    std::cout << '\n';
}
void TeamData::output_data_freezed(const int problem_cnt) {
    for (int j = 0; j < problem_cnt; j++) {
        if (sub.ac_tim[j]) {
            if (sub.submit_cnt_bfac[j])
                std::cout << "+" << sub.submit_cnt_bfac[j];
            else
                std::cout << "+";
        } else if (!subf.submit_cnt[j]) {
            if (sub.submit_cnt[j])
                std::cout << "-" << sub.submit_cnt[j];
            else
                std::cout << ".";
        } else {
            if (sub.submit_cnt[j])
                std::cout << "-" << sub.submit_cnt[j] << "/" << subf.submit_cnt[j];
            else
                std::cout << "0/" << subf.submit_cnt[j];
        }
        if (j != problem_cnt - 1)
            std::cout << " ";
    }
}
void TeamData::output_data_replace(const std::string &replaced_team) {
    std::cout << team_name << " " << replaced_team << " " << sub.ac_cnt << " " << penalty << '\n';
}
void TeamData::unfreeze(const int pid) {
    sub.submit_tot += subf.submit_cnt[pid];
    subf.submit_tot -= subf.submit_cnt[pid];
    for (int j = 0; j < 4; j++) {
        if (!subf.las_sub[pid][j].tim)
            continue;
        sub.las_sub[pid][j] = subf.las_sub[pid][j];
        subf.las_sub[pid][j] = {0, 0, 0, 0, 0};
    }
    sub.submit_cnt[pid] += subf.submit_cnt[pid];
    subf.submit_cnt[pid] = 0;
    sub.submit_cnt_bfac[pid] += subf.submit_cnt_bfac[pid];
    subf.submit_cnt_bfac[pid] = 0;
    if (subf.ac_tim[pid]) {
        auto pos = lower_bound(ac_tim_sort.begin(), ac_tim_sort.end(), subf.ac_tim[pid]);
        ac_tim_sort.insert(pos, subf.ac_tim[pid]);
        sub.ac_cnt++;
        subf.ac_cnt--;
        sub.ac_tim[pid] = subf.ac_tim[pid];
        subf.ac_tim[pid] = 0;
        penalty += 20 * sub.submit_cnt_bfac[pid] + sub.ac_tim[pid];
    }
}
bool TeamData::operator<(const TeamData &x) const {
    if (sub.ac_cnt != x.sub.ac_cnt)
        return sub.ac_cnt > x.sub.ac_cnt;
    if (penalty != x.penalty)
        return penalty < x.penalty;
    if (sub.ac_cnt) {
        for (int i = sub.ac_cnt - 1; i >= 0; i--)
            if (ac_tim_sort[i] != x.ac_tim_sort[i])
                return ac_tim_sort[i] < x.ac_tim_sort[i];
    }
    return team_name < x.team_name;
}

#ifndef ICPC_H
#define ICPC_H

struct InputMessage {
    int opt;
    std::string data[4];
};

class CompareTeam {
  public:
    bool operator()(const int &a, const int &b) const;
};

void ReadMsg(InputMessage &msg);
void AddTeam(const std::string &team_name);
void StartCompetition(const int duration_time, int problem_count);
void SubmitProblem(const std::string &problem_name, const std::string &team_name, const int submit_status, const int tim);
void FlushBoard();
void FreezeBoard();
void OutputData();
void ScrollBoard();
void QueryRanking(const std::string &team_name);
void QuerySubmission(const std::string &team_name, const std::string &problem_name, const int submit_status);
bool OperateMsg(const InputMessage &msg);

#endif




int started_flag = 0, freeze_flag = 0;
int team_cnt = 0, problem_cnt = 0, submit_cnt = 0;

std::unordered_map<std::string, int> team_key;

std::vector<TeamData> team_list;

std::set<int, CompareTeam> rank_list;

void skipword(const char end_sign = ' ') {
    getchar();
    while (getchar() != end_sign)
        ;
}

void rdstr(std::string &s, const int max_len = 30) {
    char str[max_len];
    scanf("%s", str);
    s = static_cast<std::string>(str);
    return;
}

void ReadMsg(InputMessage &msg) {
    std::string option;
    rdstr(option);
    if (option == "ADDTEAM") {
        msg.opt = kAdd;
        rdstr(msg.data[0]);
    } else if (option == "START") {
        msg.opt = kStart;
        skipword();
        rdstr(msg.data[0]);
        skipword();
        rdstr(msg.data[1]);
    } else if (option == "SUBMIT") {
        // tagggg = 1;
        msg.opt = kSub;
        rdstr(msg.data[0]);
        skipword();
        rdstr(msg.data[1]);
        skipword();
        rdstr(msg.data[2]);
        skipword();
        rdstr(msg.data[3]);
    } else if (option == "FLUSH") {
        msg.opt = kFlush;
    } else if (option == "FREEZE") {
        msg.opt = kFreeze;
    } else if (option == "SCROLL") {
        msg.opt = kScroll;
    } else if (option == "QUERY_RANKING") {
        msg.opt = kQrank;
        rdstr(msg.data[0]);
    } else if (option == "QUERY_SUBMISSION") {
        msg.opt = kQsub;
        rdstr(msg.data[0]);
        skipword('=');
        rdstr(msg.data[1]);
        skipword('=');
        rdstr(msg.data[2]);
    } else if (option == "END") {
        msg.opt = kEnd;
    }
}

bool CompareTeam::operator()(const int &a, const int &b) const { return a == b ? false : team_list[a] < team_list[b]; }

void AddTeam(const std::string &team_name) {
    if (!started_flag) {
        if (!team_key[team_name]) {
            std::cout << kAddTeamSuc << '\n';
            team_key[team_name] = team_cnt;
            team_list.push_back(TeamData(team_name, team_cnt));
            rank_list.insert(team_cnt);
            team_cnt++;
        } else {
            std::cout << kAddTeamDuplicated << '\n';
        }
    } else {
        std::cout << kAddTeamAfterStarted << '\n';
    }
    return;
}

void StartCompetition(const int duration_time, int problem_count) {
    if (!started_flag) {
        started_flag = 1;
        problem_cnt = problem_count;
        int rk_cnt = 1;
        for (auto it : rank_list)
            team_list[it].rank = rk_cnt++;
        std::cout << kStartSuc << '\n';
    } else {
        std::cout << kStartAlready << '\n';
    }
    return;
}

void SubmitProblem(const std::string &problem_name, const std::string &team_name, const int submit_status, const int tim) {
    int problem_key = problem_name[0] - 'A';
    Submission new_sub(team_key[team_name], problem_key, submit_status, tim, submit_cnt++);
    if (!freeze_flag) {
        if (submit_status == kAC) {
            rank_list.erase(new_sub.tid);
            team_list[new_sub.tid].submit(new_sub);
            rank_list.insert(new_sub.tid);
        } else {
            team_list[new_sub.tid].submit(new_sub);
        }
    } else {
        team_list[new_sub.tid].submitf(new_sub);
    }
}

void FlushBoard() {
    int rk_cnt = 0;
    for (auto it : rank_list) {
        team_list[it].rank = ++rk_cnt;
    }
    std::cout << kFlushSuc << '\n';
    return;
}

void FreezeBoard() {
    if (!freeze_flag) {
        freeze_flag = 1;
        std::cout << kFreezeSuc << '\n';
    } else {
        std::cout << kFreezeFail << '\n';
    }
    return;
}

void ScrollBoard() {
    if (!freeze_flag) {
        std::cout << kScrollFail << '\n';
        return;
    }
    bool found_frz;
    int rk_cnt = 1;
    std::cout << kScrollSuc << '\n';
    for (auto it: rank_list) {
        team_list[it].output_info(rk_cnt++);
        team_list[it].output_data_freezed(problem_cnt);
        std::cout << '\n';
    }
    for (auto it: rank_list)
        if (team_list[it].frozen()) {
            for (int i = 0; i < problem_cnt; i++) {
                if (!team_list[it].aced_problem(i) && team_list[it].frozen(i)) {
                    team_list[it].unfreeze(i);
                }
            }
        }
    static std::vector<int> last_place;
    last_place.assign(team_cnt, 0);
    auto it_las = rank_list.end();
    do {
        found_frz = 0;
        auto it = it_las;
        if (it == rank_list.begin())
            break;
        do {
            it_las = it;
            it--;
            if (team_list[*it].frozen()) {
                found_frz = 1;
                auto it_nex = it;
                it_nex++;
                int las_nex;
                if (it_nex == rank_list.end())
                    las_nex = -1;
                else
                    las_nex = *it_nex;
                rank_list.erase(*it);
                for (int i = last_place[*it]; i < problem_cnt; i++) {
                    if (team_list[*it].frozen(i)) {
                        team_list[*it].unfreeze(i);
                        last_place[*it] = i + 1;
                        break;
                    }
                }
                it_nex = rank_list.insert(*it).first;
                it_nex++;
                if (it_nex != rank_list.end() && las_nex != *it_nex)
                    team_list[*it].output_data_replace(team_list[*it_nex].team_name);
                break;
            }
        } while (it != rank_list.begin());
    } while (found_frz);
    rk_cnt = 1;
    for (auto it: rank_list) {
        team_list[it].output_info(rk_cnt);
        team_list[it].output_data(problem_cnt);
        team_list[it].rank = rk_cnt;
        rk_cnt++;
    }
    freeze_flag = 0;
}

void QueryRanking(const std::string &team_name) {
    if (team_key.find(team_name) == team_key.end())
        std::cout << kQrankFail << '\n';
    else {
        std::cout << kQrankSuc << '\n';
        if (freeze_flag)
            std::cout << kQrankWarn << '\n';
        std::cout << team_name << " NOW AT RANKING " << team_list[team_key[team_name]].rank << '\n';
    }
    return;
}

inline int JudgeSubStatus(const std::string &submit_status) {
    for (int i = 0; i < 5; i++) {
        if (submit_status == kSubmitStatus[i])
            return i;
    }
    return -1;
}

void QuerySubmission(const std::string &team_name, const std::string &problem_name, const int submit_status) {
    auto iter = team_key.find(team_name);
    if (iter == team_key.end())
        std::cout << kQsubNoTeam << '\n';
    else {
        std::cout << kQsubSuc << '\n';
        int tid = iter->second;
        Submission las_sub(0, 0, 0, 0, 0);
        if (problem_name == "ALL") {
            if (submit_status == kALL) {
                for (int i = 0; i < problem_cnt; i++)
                    for (int j = 0; j < 4; j++) {
                        las_sub = std::max(las_sub, team_list[tid].last_submit(i, j));
                    }
            } else {
                for (int i = 0; i < problem_cnt; i++) {
                    las_sub = std::max(las_sub, team_list[tid].last_submit(i, submit_status));
                }
            }
        } else {
            int pid = problem_name[0] - 'A';
            if (submit_status == kALL) {
                for (int j = 0; j < 4; j++) {
                    las_sub = std::max(las_sub, team_list[tid].last_submit(pid, j));
                }
            } else {
                las_sub = std::max(las_sub, team_list[tid].last_submit(pid, submit_status));
            }
        }
        if (las_sub.tim)
            std::cout << team_name << " " << static_cast<char>(las_sub.pid + 'A') << " " << kSubmitStatus[las_sub.status] << " "
                      << las_sub.tim << '\n';
        else
            std::cout << kQsubNoSub << '\n';
    }
    return;
}

bool OperateMsg(const InputMessage &msg) {
    if (msg.opt == kAdd) {
        AddTeam(msg.data[0]);
    } else if (msg.opt == kStart) {
        StartCompetition(std::stoi(msg.data[0]), std::stoi(msg.data[1]));
    } else if (msg.opt == kSub) {
        SubmitProblem(msg.data[0], msg.data[1], JudgeSubStatus(msg.data[2]), std::stoi(msg.data[3]));
    } else if (msg.opt == kFlush) {
        FlushBoard();
    } else if (msg.opt == kFreeze) {
        FreezeBoard();
    } else if (msg.opt == kScroll) {
        ScrollBoard();
    } else if (msg.opt == kQrank) {
        QueryRanking(msg.data[0]);
    } else if (msg.opt == kQsub) {
        QuerySubmission(msg.data[0], msg.data[1], JudgeSubStatus(msg.data[2]));
    } else {
        std::cout << kEndCompetition << '\n';
        return 0;
    }
    return 1;
}

int main() {
    // freopen("../data/bigger.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    std::ios::sync_with_stdio(false);           // stop the sync with stdio
    while (true) {
        InputMessage msg;
        ReadMsg(msg);                                 // Read a message and judge its type 
        if (!OperateMsg(msg))                         // Operate the message it reads
            break;
    }
    return 0;
}