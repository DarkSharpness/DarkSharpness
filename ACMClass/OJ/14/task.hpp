# ifndef _SJTU_CPP_FINAL_TASK_HPP_
# define _SJTU_CPP_FINAL_TASK_HPP_

typedef unsigned int uint;

namespace sjtu {
    // Description for each task:
    //   task_id: uint, unique for each task;
    //   priority: uint;
    //   time: uint, (remaining) time of the task.
    struct Task {
        uint task_id;
        uint priority;
        uint time;

        explicit Task(uint _task_id = 0, uint _priority = 0, uint _time = 0) {
            task_id = _task_id;
            priority = _priority;
            time = _time;
        }

        Task(const Task &rhs) {
            task_id  = rhs.task_id;
            priority = rhs.priority;
            time = rhs.time;
        }

        ~ Task() = default;
    };

    // CPUState: idle and busy.
    enum CPUState {
        idle = 0, busy = 1
    };
}
# endif