#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
// WARNING: NO more headers allowed!

using std::pair;
using std::string;
using std::vector;
using std::map;
using std::function;
namespace final {
    class arguments {
    private:
        // WARNING: You cannot add more member variables.
        int _argc;
        char** _argv;

        int getlen(const char *ptr) {
            int cnt = 0;
            while(*ptr){
                while(*ptr == ' ') ++ptr;
                while(*ptr && *ptr != ' ') ++ptr;
                ++cnt;
            }
            return cnt;
        }
        const char *getstr(const char *ptr) {
            while(*ptr == ' ') ++ptr;
            const char *tmp = ptr;
            while(*ptr && *ptr != ' ') ++ptr;
            _argv[_argc] = new char [ptr - tmp + 1];
            memcpy(_argv[_argc],tmp,ptr - tmp);
            _argv[_argc++][ptr - tmp] = '\0';
            return *ptr ? ptr : nullptr;
        }

    public:
        arguments() : _argc(0), _argv(nullptr) {}
        explicit arguments(const string &cmd) {
            _argc = 0;
            const char *ptr = cmd.c_str();
            _argv = new char *[getlen(ptr)];
            while((ptr = getstr(ptr)));
        }
        ~arguments() {
            for(int i = 0 ; i < _argc ; ++i) 
                delete []_argv[i];
            delete []_argv;
        }
        // WARNING: You cannot modify the following functions
        int argc() const { return _argc; }
        char** argv() const { return _argv; }
    };

    // You don't need to modify shell.
    class shell {
    private:
        map<int, arguments> running_list;
    public:
        shell() = default;

        void run(int pid, const string& cmd, const function<void(int, char**)>& invoked) {
            running_list.emplace(pid, cmd);
            invoked(running_list[pid].argc(), running_list[pid].argv());
        }

        int subprocessExit(int pid, int return_value) {
            running_list.erase(pid);
            return return_value;
        }
        vector<int> getRunningList() const {
            vector<int> rt;
            for (auto& pair:running_list)rt.push_back(pair.first);
            return rt;
        }
    };
}