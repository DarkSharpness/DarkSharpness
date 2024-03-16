# ifndef _SJTU_CPP_FINAL_CPU_HPP_
# define _SJTU_CPP_FINAL_CPU_HPP_

# include <vector>
# include "task.hpp"

using namespace std;

typedef unsigned int uint;

namespace sjtu {
    // CPU base class, modifications is not allowed.
    class CPU {
    protected:
        CPUState state;
        vector<Task> tasks;

    public:
        CPU() : tasks() {
            state = idle;
        }

        // Add a new task.
        int addTask(const Task &t) {
            tasks.push_back(t);
            return 1;
        }

        // Change the priority of one process, return 1 if success and return 0 if fail.
        int changePriority(uint task_id, uint priority) {
            for (auto &task: tasks)
                if (task.task_id == task_id) {
                    task.priority = priority;
                    return 1;
                }
            return 0;
        }

        virtual pair<CPUState, uint> run() = 0;

        virtual ~CPU() = default;
    };

    // FCFS method based CPU.
    class CPU_FCFS : public CPU {
        // TODO: complete the FCFS method.
        pair <CPUState, uint> run() override {
            for(int i = 0 ; i < (int)tasks.size() ; ++i)
                if(tasks[i].time)  {
                    --tasks[i].time;
                    return make_pair(state = busy,tasks[i].task_id);
                }
            return make_pair(state = idle,0u);
        }
    };

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
      public:
        pair <CPUState, uint> run() override {
            int u = -1;
            uint MIN = 1919810 << 11;
            for(int i = 0 ; i < (int)tasks.size() ; ++i)
                if(tasks[i].time && tasks[i].time < MIN) 
                    MIN = tasks[u = i].time;
            if(u == -1) return make_pair(state = idle,0u);
            else {
                --tasks[u].time;
                return make_pair(state = busy,tasks[u].task_id);
            }
        }
    };

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
        pair <CPUState, uint> run() override {
            int u = -1;
            uint MIN = 1919810u << 11;
            for(int i = 0 ; i < (int)tasks.size() ; ++i)
                if(tasks[i].time && tasks[i].priority < MIN) 
                    MIN = tasks[u = i].priority;
            if(u == -1) return make_pair(state = idle,0u);
            else {
                --tasks[u].time;
                return make_pair(state = busy,tasks[u].task_id);
            }
        }
    };
}

# endif