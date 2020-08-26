#ifndef _DoseProgram_
#define _DoseProgram_



#include <globals.h>

void nextion_callback_setup(void);
void pedal_filling_callback(void* ptr);
void auto_filling_callback(void* ptr);
void calib1_btn_callback(void * ptr);
void calib2_btn_callback(void * ptr);
void calib3_btn_callback(void * ptr);
void calib4_btn_callback(void * ptr);
void calib5_btn_callback(void * ptr);

void chk1_callback(void* ptr);
void chk2_callback(void* ptr);
void chk3_callback(void* ptr);
void chk4_callback(void* ptr);
void chk5_callback(void* ptr);

void calib_continue_callback(void* ptr);
void calib_radius_callback(void* ptr);
void calib_volume_callback(void* ptr);
void calib_complete_callback(void* ptr);
void press_until_pipe_fills_press_callback(void* ptr);
void press_until_pipe_fills_release_callback(void* ptr);
void left_to_fill_callback(void* ptr);
void start_fill_callback(void* ptr);
void end_fill_callback(void* ptr);
void auto_fill_start_callback(void* ptr);
void ok_btn_callback(void* ptr);
void rpm_slider_callback(void* ptr);


// HELPERS 
void read_callibrations();

// OPERATIONS
void callibrate_operation(void);
void auto_operation(void);
void config_operation(void);
void config_auto_operation(void);


// PEDAL CALLBACKS
void pedal_callibration_press_callback(void*);
void pedal_callibration_release_callback(void*);
void pedal_empty_callback(void*);
void pedal_default_fill_callback(void*);
void pedal_default_fill_release_callback(void*);
void pedal_auto_fill_callback(void*);



#endif