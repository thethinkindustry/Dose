#ifndef _DoserGlobals_
#define _DoserGlobals_
#include <DosingController.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>
#include <EEPROMController.h>
#include <CircularBuffer.h>
#include <program.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

#define nexSerial Serial1
#define NOTHING_TO_DOSE -1


#define PUL_PIN 11
#define DIR_PIN 12
#define EN_PIN 13 



extern AVR_StepMotor motor;
extern DosingController doser;
extern AVR_Button pedal;
extern DosingConfiguration cfgOnEdit;
extern EEPROMController eeprm;

namespace state
{
    extern bool dosing_manual;
    extern int remaining_to_dose;
    extern bool callibrating_by_time;
    extern uint64_t last_total_steps;
    extern uint64_t total_steps_runned;
    extern uint64_t last_ticks_us;
    extern uint64_t last_fill_time;
    extern uint32_t delay_between_fills;
    extern uint32_t fill_amount;
    extern uint32_t* keyboard_target;
    extern void (*operation)(void);
    extern CircularBuffer<uint8_t> txtBuf;
}




extern ButtonFunc pedal_callback;
extern ButtonFunc pedal_release_callback;



//************************************
// NEXTION BUTTONS //
extern NexButton btn_calib1;
extern NexButton btn_calib2;
extern NexButton btn_calib3;
extern NexButton btn_calib4;
extern NexButton btn_calib5;
extern NexCheckbox chk1;
extern NexCheckbox chk2;
extern NexCheckbox chk3;
extern NexCheckbox chk4;
extern NexCheckbox chk5;
extern NexButton btn_calib_save;

extern NexButton btn_clb_fill_pipe;
extern NexButton btn_clb_start_fill;
extern NexButton btn_numpad_ok;

extern NexText txt_fill_amount;
extern NexText txt_delay;
extern NexText txt_pipe_r;
extern NexText txt_volume;
extern NexText txt_numpad;

extern NexButton btn_fill_by_foot;


//PAGE_PIPE
extern NexButton btn_pipe_filling;
extern NexButton btn_start_pedal_filling;

//PAGE_PIPE_2
extern NexButton btn_pipe_filling2;
extern NexButton btn_auto_filling_config;

extern NexButton btn_start_auto_filling;
extern NexButton btn_stop_auto_filling;
extern NexButton btn_stop_pedal;


extern NexTouch* nex_listen_list[];
#endif