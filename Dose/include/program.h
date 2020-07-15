#ifndef _DoseProgram_
#define _DoseProgram_


#include <ITEADLIB_Arduino_Nextion/Nextion.h>
#include <globals.h>


void callibrate_by_time(void*);
void pedal_callibrate_by_time(void*);
void end_callibration(void*);
void manual_dosing(void*);
void settings_setRPM_callback(void* ptr);
void save_current_config(void);
void save_config_on_edit(void);
void set_pedal_callbacks_todefault(void);
void default_operation(void*);
void default_pedal_callback(void*);
void default_pedal_release_callback(void*);
void automatic_dosing_callback(void*);
void automatic_dosing_pedal_callback(void*);


#endif