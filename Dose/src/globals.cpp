#include <globals.h>


EEPROMController eeprm = EEPROMController(1024);

namespace state
{
    uint64_t last_total_steps = 0;
    uint64_t total_steps_runned = 0;
    uint64_t last_ticks_us = 0;
    int remaining_to_dose = 0;
    bool callibrating_by_time = false;
    bool dosing_manual = true;
    void (*operation)(void*);
    CircularBuffer<uint8_t> txtBuf = CircularBuffer<uint8_t>(UINT32_C(100));
}

NexButton btn_calib1 = NexButton(2,7,"btn_calib1");
NexButton btn_calib2 = NexButton(2,8,"btn_calib2");
NexButton btn_calib3 = NexButton(2,9,"btn_calib3");
NexButton btn_calib4 = NexButton(2,10,"btn_calib4");
NexButton btn_calib5 = NexButton(2,11,"btn_calib5");

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
  &btn_pipe_filling,
  &btn_start_pedal_filling,
  &btn_pipe_filling2,
  &btn_auto_filling_config,
  &btn_start_auto_filling,
  &btn_stop_auto_filling,
  &btn_stop_pedal,
  NULL
};

