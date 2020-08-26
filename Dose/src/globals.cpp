#include <globals.h>

EEPROMController eeprm = EEPROMController(1024);

AVR_StepMotor motor = AVR_StepMotor(EN_PIN, DIR_PIN, PUL_PIN);
AVR_Button pedal = AVR_Button(7);
DosingController doser = DosingController(&motor);

DosingConfiguration current_cfg = DosingConfiguration();
//SoftwareSerial debug_serial(2, 3);
SoftwareSerial nSerial(2,3);
//Nextion* next = Nextion::GetInstance(Serial);

namespace state
{
    ProgramMode mode = ProgramMode::Manual;
    uint64_t last_total_steps = 0;
    uint64_t callibration_steps = 0;
    uint32_t remaining_to_fill = 0;
    uint32_t auto_last_fill_ticks = 0;
    volatile uint32_t delay_between_fills = 0;
    uint32_t steps_before_callibration = 0;
    void (*operation)(void);
    NexText& numpad_target;
    NumpadMode numpad_mode;
    char txt_buf[40];
    bool auto_last_state = false;
    bool dosed = false;
}

// PAGE MAIN
const char* p0= "page_main";
//NexPage page_main( 0,p0);
NexPage page_main(0,0, p0);
NexButton filling_btn( 0, 2, "b_filling", p0); 
NexButton calib_btn( 0, 3, "b_calib", p0);
//NexButton setting_btn( 0, 4, "b_setting", &page_main);
//NexButton about_btn( 0, 5, "b_about", &page_main);

// PAGE FILLING
const char* p1 = "page_filing";
//NexPage page_filling( 1, p1);
NexButton pedal_filling_btn( 1, 2, "b0");
NexButton auto_filling_btn( 1, 3, "b1");
//NexButton filling_back_btn( 1, 4, "b2", &page_filling);

// PAGE CALIB
const char* p2 = "page_calib";
//NexPage page_calib( 2, p2); 
const char* calib1_btn_name = "btn_calib1";
const char* calib2_btn_name = "btn_calib2";
const char* calib3_btn_name = "btn_calib3";
const char* calib5_btn_name = "btn_calib5";
const char* calib4_btn_name = "btn_calib4";


NexButton calib1_btn( 2, 7, calib1_btn_name, p2);
NexButton calib2_btn( 2, 8, calib2_btn_name, p2);
NexButton calib3_btn( 2, 9, calib3_btn_name, p2);
NexButton calib4_btn( 2, 10, calib4_btn_name, p2);
NexButton calib5_btn( 2, 11, calib5_btn_name, p2);
NexCheckbox chk1( 2, 2, "c1");
NexCheckbox chk2( 2, 3, "c2");
NexCheckbox chk3( 2, 4, "c3");
NexCheckbox chk4( 2, 5, "c4");
NexCheckbox chk5( 2, 6, "c5");

// PAGE CONFIG
const char* p3 = "page_config";
//NexPage page_config( 3, p3);
NexButton calib_back_btn( 3, 2, "b_back");
NexButton calib_continue_btn( 3, 3, "b_save");;
NexText calib_name_txt( 3, 4, "ct0", p3);
NexNumber calib_radius_txt( 3, 5, "ct1",p3);
NexNumber calib_volume_txt( 3, 6, "ct2", p3);
NexVariable _radius(3, 7, "_radius", p3);
NexVariable _volume(3, 8, "_volume", p3);

// PAGE CALIB S
const char* p4 = "page_calib_s";
//NexPage page_calib_s( 4, p4);
NexButton calib_complete_btn( 4, 2, "b_save");

// PAGE PEDAL
const char* p5 = "page_pedal";
//NexPage page_pedal( 5, p5);
NexButton end_fill_btn( 5, 2, "b_stop_pedal");
NexNumber  left_to_fill_txt( 5, 3, "pt0", p5);

// PAGE PIPE
const char* p6 = "page_pipe";
NexPage page_pipe(6,0,"page_pipe");
NexButton press_until_pipe_fills_btn(6, 2, "b_fillpipe");
NexButton start_fill_btn(6, 3, "b_startfill");


// PAGE FILL AUTO
const char* p7 = "page_fill_auto";
//NexPage page_fill_auto( 7, p7);
NexButton auto_fill_back_btn( 7, 2, "b1");
NexButton auto_fill_start_btn( 7, 3, "b_startauto");
NexNumber auto_to_fill_txt( 7, 4, "at0", p7);
NexNumber auto_wait_time_txt( 7, 5, "at1", p7);

// PAGE NUMPAD 1
const char p8[] PROGMEM = "page_numpad1";
//NexPage page_numpad1( 8, p8);
/*
NexButton b0_btn( 8, 2 ,"b0", &page_numpad1);
NexButton b1_btn( 8, 3 ,"b1", &page_numpad1);
NexButton b2_btn( 8, 4 ,"b2", &page_numpad1);
NexButton b3_btn( 8, 5 ,"b3", &page_numpad1);
NexButton b4_btn( 8, 6 ,"b4", &page_numpad1);
NexButton b5_btn( 8, 7 ,"b5", &page_numpad1);
NexButton b6_btn( 8, 8 ,"b6", &page_numpad1);
NexButton b7_btn( 8, 9 ,"b7", &page_numpad1);
NexButton b8_btn( 8, 10 ,"b8", &page_numpad1);
NexButton b9_btn( 8, 11 ,"b9", &page_numpad1);
NexButton clr_btn( 8, 12 ,"b10", &page_numpad1);
*/
//NexButton ok_btn( 8, 13 ,"b11");
//NexText input_txt( 8, 15 ,"nt0", &page_numpad1);

// PAGE SETTINGS
const char* p9 = "page_settings"; 
NexNumber setting_rpm(9, 3, "n0", p9);
NexSlider setting_rpm_slider(9,4,"h0", p9);


NexTouch* nex_listen_list[] = {
  //&filling_btn,
  //&calib_btn,
  //&setting_btn,
  //&about_btn,

  &pedal_filling_btn,
  &auto_filling_btn,
  //&filling_back_btn,

  &calib1_btn,
  &calib2_btn, 
  &calib3_btn, 
  &calib4_btn, 
  &calib5_btn, 
  &chk1,
  &chk2, 
  &chk3, 
  &chk4, 
  &chk5,

  //&calib_back_btn,
  &calib_continue_btn,
  //&calib_name_txt,
  //&calib_radius_txt,
  //&calib_volume_txt,
  //&_radius,
  //&_volume,

  &calib_complete_btn,

  &end_fill_btn,
  //&left_to_fill_txt,
  
  //&page_pipe,
  &press_until_pipe_fills_btn,
  &start_fill_btn,

  //&auto_fill_back_btn,
  &auto_fill_start_btn,
  //&auto_to_fill_txt,
  //&auto_wait_time_txt,


  //&b0_btn,
  //&b1_btn,
  //&b2_btn,
  //&b3_btn,
  //&b4_btn,
  //&b5_btn,
  //&b6_btn,
  //&b7_btn,
  //&b8_btn,
  //&b9_btn,
  //&clr_btn,
  //&ok_btn,
  //&input_txt,
  &setting_rpm_slider,
  NULL
};



/*
NexButton btn_calib1 = NexButton(2,7,"btn_calib1");
NexButton btn_calib2 = NexButton(2,8,"btn_calib2");
NexButton btn_calib3 = NexButton(2,9,"btn_calib3");
NexButton btn_calib4 = NexButton(2,10,"btn_calib4");
NexButton btn_calib5 = NexButton(2,11,"btn_calib5");

NexCheckbox chk1 = NexCheckbox(2, 1, "chk1");
NexCheckbox chk2 = NexCheckbox(2, 1, "chk2");
NexCheckbox chk3 = NexCheckbox(2, 1, "chk3");
NexCheckbox chk4 = NexCheckbox(2, 1, "chk4");
NexCheckbox chk5 = NexCheckbox(2, 1, "chk5");

NexButton btn_calib_save = NexButton(4, 1, "b_save");

NexButton btn_clb_fill_pipe = NexButton(5,1, "asd");
NexButton btn_clb_start_fill = NexButton(5,1, "asd");

NexButton btn_fill_by_foot = NexButton(0, 1, "b0");
NexButton btn_numpad_ok = NexButton(10, 1, "b11");
NexText txt_fill_amount = NexText(9, 1, "t0");
NexText txt_delay = NexText(9, 1, "t1");

NexText txt_pipe_r = NexText(3, 1, "r");
NexText txt_volume = NexText(3, 2, "v");
NexText txt_numpad = NexText(10, 1, "t0");

//PAGE_PIPE
NexButton btn_pipe_filling =NexButton(5,2,"b_fillpipe");
NexButton btn_start_pedal_filling=NexButton(5,3,"b_startfill");

//PAGE_PIPE_2
NexButton btn_pipe_filling2 =NexButton(6,2,"b_fillpipe");
NexButton btn_auto_filling_config=NexButton(6,3,"b_startfill");
//Page_FILL_AUTO
NexButton btn_start_auto_filling =NexButton(7,3,"b_startauto");
//PAGE_AUTO
NexButton btn_stop_auto_filling =NexButton(9,2,"b_stop_auto");
//PAGE_PEDAL
NexButton btn_stop_pedal=NexButton(4,2,"b_stop_pedal");


NexTouch* nex_listen_list[] = {
  &btn_calib1,
  &btn_calib3,
  &btn_calib3,
  &btn_calib4,
  &btn_calib5,
  &chk1,
  &chk2,
  &chk3,
  &chk4,
  &chk5,
  &btn_calib_save,
  &txt_fill_amount,
  &txt_delay,
  &txt_pipe_r,
  &txt_volume,
  &btn_fill_by_foot,
  &btn_numpad_ok,
  &btn_pipe_filling,
  &btn_start_pedal_filling,
  &btn_pipe_filling2,
  &btn_auto_filling_config,
  &btn_start_auto_filling,
  &btn_stop_auto_filling,
  &btn_stop_pedal,
  NULL
};
*/

