#ifndef _StaticTimer_
#define _StaticTimer_

#include <stdint.h>

using TimerTask = void(*)(void*);

enum  TimerResolution
{
    microseconds,
    milliseconds
};


class StaticTimer
{
    private:
    static const int max_tasks = 4;
    uint64_t period;
    uint64_t last_ticks;
    TimerTask tasks[max_tasks];
    int index = 0;
    inline void doTasks();

    public:
    StaticTimer();
    StaticTimer(uint64_t p);
    bool addTask(TimerTask t);
    void update(uint64_t ticks);
};


#endif