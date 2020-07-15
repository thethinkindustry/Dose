#ifndef _DoserGlobals_
#define _DoserGlobals_
#include <DosingController.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>

#define NOTHING_TO_DOSE -1



extern AVR_StepMotor motor;
extern DosingController doser;
extern AVR_Button pedal;
extern DosingConfiguration cfgOnEdit;

namespace state
{
    extern bool dosing_manual;
    extern int remaining_to_dose;
    extern bool callibrating_by_time;
    extern uint64_t last_total_steps;
    extern uint64_t total_steps_runned;
    extern uint64_t last_ticks_us;
    extern void (*operation)(void*);
    extern char txtBuf[];
}




extern ButtonFunc pedal_callback;
extern ButtonFunc pedal_release_callback;


//************************************
// NEXTION BUTTONS //



#endif