#include <globals.h>

namespace state
{
    uint64_t last_total_steps = 0;
    uint64_t total_steps_runned = 0;
    uint64_t last_ticks_us = 0;
    int remaining_to_dose = 0;
    bool callibrating_by_time = false;
    bool dosing_manual = true;
    void (*operation)(void*) = default_operation;
    char txtBuf[50] = {0};
}


