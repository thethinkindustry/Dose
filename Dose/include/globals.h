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
#include <Nextion.h>

//#define nexSerial Serial1
#define nexSerial nSerial
#define debug_serial Serial
#define NOTHING_TO_DOSE -1


#define PUL_PIN 11
#define DIR_PIN 12
#define EN_PIN 13 

#define FF(X) (const char*)F(X)


extern AVR_StepMotor motor;
extern DosingController doser;
extern AVR_Button pedal;
extern DosingConfiguration current_cfg;
//extern SoftwareSerial debug_serial;
extern EEPROMController eeprm;
extern SoftwareSerial nSerial;
//extern Nextion* next;


enum class ProgramMode
{
  Manual,
  Auto,
  Callibration
};



enum NumpadMode
{
  none,
  left_to_fill,
  calib_radius,
  calib_volume,
};


namespace state
{
    extern ProgramMode mode;
    extern uint32_t remaining_to_fill;
    extern uint64_t last_total_steps;
    extern uint64_t callibration_steps;
    extern uint32_t steps_before_callibration;
    extern volatile uint32_t delay_between_fills;
    extern uint32_t fill_amount;
    extern void (*operation)(void);
    extern NexText& numpad_target;
    extern NumpadMode numpad_mode;
    extern char txt_buf[40];
    extern uint32_t auto_last_fill_ticks;
    extern bool auto_last_state;
    extern bool dosed;
}

extern ButtonFunc pedal_callback;
extern ButtonFunc pedal_release_callback;

//************************************
// NEXTION BUTTONS //

// PAGE MAIN
extern NexPage page_main;
extern NexButton filling_btn;
extern NexButton calib_btn;
//extern NexButton setting_btn;
//extern NexButton about_btn;

// PAGE FILLING
extern NexPage page_filing;
extern NexButton pedal_filling_btn;
extern NexButton auto_filling_btn;
//extern NexButton filling_back_btn;


// PAGE CALIB
extern NexPage page_calib;
extern NexButton calib1_btn;
extern NexButton calib2_btn;
extern NexButton calib3_btn;
extern NexButton calib4_btn;
extern NexButton calib5_btn;
extern NexCheckbox chk1;
extern NexCheckbox chk2;
extern NexCheckbox chk3;
extern NexCheckbox chk4;
extern NexCheckbox chk5;

// PAGE CONFIG
extern NexPage page_config;
extern NexButton calib_back_btn;
extern NexButton calib_continue_btn;
extern NexText calib_name_txt;
extern NexNumber calib_radius_txt;
extern NexNumber calib_volume_txt;
extern NexVariable _radius;
extern NexVariable _volume;

// PAGE CALIB S
extern NexPage page_calib_s;
extern NexButton calib_complete_btn;

// PAGE PEDAL
extern NexPage page_pedal;
extern NexButton end_fill_btn;
extern NexNumber left_to_fill_txt;

// PAGE PIPE
extern NexPage page_pipe;
extern NexButton press_until_pipe_fills_btn;
extern NexButton start_fill_btn;


// PAGE FILL AUTO
extern NexPage page_fill_auto;
extern NexButton auto_fill_back_btn;
extern NexButton auto_fill_start_btn;
extern NexNumber auto_to_fill_txt;
extern NexNumber auto_wait_time_txt;

// PAGE NUMPAD 1
extern NexPage page_numpad1;
/*
extern NexButton b0_btn;
extern NexButton b1_btn;
extern NexButton b2_btn;
extern NexButton b3_btn;
extern NexButton b4_btn;
extern NexButton b5_btn;
extern NexButton b6_btn;
extern NexButton b7_btn;
extern NexButton b8_btn;
extern NexButton b9_btn;
extern NexButton clr_btn;
*/
//extern NexButton ok_btn;
//extern NexText input_txt;

// PAGE SETTINGS
extern NexNumber setting_rpm;
extern NexSlider setting_rpm_slider;


extern NexTouch* nex_listen_list[];
#endif