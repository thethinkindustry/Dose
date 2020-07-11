#include <StaticTimer.h>

StaticTimer::StaticTimer(uint64_t p)
:period{p}
{
    last_ticks = 0;
}

bool StaticTimer::addTask(TimerTask t)
{
    tasks[index] = t;
    index++;
}

void StaticTimer::update(uint64_t ticks)
{
    if(period < (ticks - last_ticks)) {
        last_ticks = ticks;
        doTasks();

    }
}

inline void StaticTimer::doTasks()
{
    for(int i = 0; i<index; i++)
    {
        (*tasks[i])(nullptr);
    }
}