#include <globals.h>

EEPROMController eeprm = EEPROMController(1024);

AVR_StepMotor motor = AVR_StepMotor(EN_PIN, DIR_PIN, PUL_PIN);
AVR_Button pedal = AVR_Button(7);
DosingController doser = DosingController(&motor);

DosingConfiguration cfgOnEdit = DosingConfiguration();


namespace state
{
    uint64_t last_total_steps = 0;
    uint64_t total_steps_runned = 0;
    uint64_t last_ticks_us = 0;
    uint64_t last_fill_time = 0;
    uint32_t delay_between_fills = 0;
    uint32_t fill_amount;
    uint32_t* keyboard_target = nullptr;
    int remaining_to_dose = 0;
    bool callibrating_by_time = false;
    bool dosing_manual = true;
    void (*operation)(void);
    CircularBuffer<uint8_t> txtBuf = CircularBuffer<uint8_t>(UINT32_C(100));
}

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

