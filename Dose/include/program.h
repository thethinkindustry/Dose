#ifndef _DoseProgram_
#define _DoseProgram_


#include <Nextion.h>
#include <globals.h>

void nextion_callback_setup(void);

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


//NEXTION BUTTON CALLBACKS

void btn_calib1_POP_callback(void* ptr); 

void btn_calib2_POP_callback(void* ptr); 
  
void btn_calib3_POP_callback(void* ptr); 
 
void btn_calib4_POP_callback(void* ptr); 
  
void btn_calib5_POP_callback(void* ptr);

void btn_pipe_filling_POP_callback(void* ptr);

void btn_start_pedal_filling_POP_callback(void* ptr);  

void btn_pipe_filling2_POP_callback(void* ptr);
  
void btn_auto_filling_config_POP_callback(void* ptr);  
  
void btn_start_auto_filling_POP_callback(void* ptr);  

void btn_stop_auto_filling_POP_callback(void* ptr);

void btn_stop_pedal_POP_callback(void* ptr);

#endif