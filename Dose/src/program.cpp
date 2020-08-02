#include <Nextion.h>
#include <globals.h>
#include <program.h>
#include <string.h>

void nextion_callback_setup(void){
 btn_calib1.attachPush(btn_calib1_POP_callback);
 btn_calib2.attachPush(btn_calib2_POP_callback);
 btn_calib3.attachPush(btn_calib3_POP_callback);
 btn_calib4.attachPush(btn_calib4_POP_callback);
 btn_calib5.attachPush(btn_calib5_POP_callback);

 chk1.attachPop(chk1_callback);
 chk2.attachPop(chk1_callback);
 chk3.attachPop(chk1_callback);
 chk4.attachPop(chk1_callback);
 chk5.attachPop(chk1_callback);
 
 btn_calib_save.attachPush(end_callibration);
 btn_clb_fill_pipe.attachPush(btn_pipe_filling2_POP_callback);
 btn_clb_start_fill.attachPop(callibrate_by_time_callback);

 //btn_numpad_ok.attachPush(btn_numpad_ok_callback);
 
 btn_pipe_filling.attachPush(btn_pipe_filling_POP_callback);
 btn_start_pedal_filling.attachPush(btn_start_pedal_filling_POP_callback);

 btn_pipe_filling2.attachPush(btn_pipe_filling2_POP_callback);
 //btn_auto_filling_config.attachPush(btn_auto_filling_config_POP_callback);

 btn_start_auto_filling.attachPush(btn_start_auto_filling_POP_callback);

 btn_stop_auto_filling.attachPush(btn_stop_auto_filling_POP_callback);

 btn_stop_pedal.attachPush(btn_stop_pedal_POP_callback);

}

void callibrate_by_time_callback(void* ptr)
{
    //state::operation = callibrate_by_time;
    pedal_callback = pedal_callibrate_by_time;
    //pedal_release_callback = pedal_callibrate_release;
    state::last_total_steps = motor.getTotalSteps();
    state::last_ticks_us = micros();
}

void save_current_config(void)
{
    eeprm.save_configuration(cfgOnEdit);
}

void save_config_on_edit(void)
{
    eeprm.save_configuration(cfgOnEdit);
}

void pedal_callibrate_by_time(void* d)
{
    doser.dose();

    
}

void pedal_callibrate_release(void* ptr)
{
    doser.stop();
    
}

void end_callibration()
{
    static char buf[10] = {0};
    txt_volume.getText(buf, 10);
    cfgOnEdit.volume =  atoi(buf);
    txt_pipe_r.getText(buf, 10);
    cfgOnEdit.pipe_radius = atoi(buf);
    cfgOnEdit.motor_steps = motor.getSteps();
    cfgOnEdit.motor_rpm = motor.getRPM();
    cfgOnEdit.work_time = 0;
    cfgOnEdit.steps_to_run = motor.getTotalSteps() - state::last_total_steps;
    save_config_on_edit();
    state::operation = default_operation;
    set_pedal_callbacks_todefault();
    
}

void default_pedal_callback(void*)
{
    if(state::dosing_manual){
        doser.dose();
    }

}

void automatic_dosing_pedal_callback(void*)
{
    static char buf[10] = {0};
    if(!(state::remaining_to_dose == NOTHING_TO_DOSE) && !doser.isDosing())
    {
        doser.dose();
        state::remaining_to_dose--;
    }
    itoa(state::remaining_to_dose +1, buf, 3);
    txt_fill_amount.setText(buf);
}

void automatic_dosing_at_exit(void* ptr)
{
    state::operation = default_operation;

    set_pedal_callbacks_todefault();
}

void default_pedal_release_callback(void*)
{
    if(state::dosing_manual)
        doser.stop();
}

void set_pedal_callbacks_todefault(void)
{
    pedal_callback = default_pedal_callback;
    pedal_release_callback = default_pedal_release_callback;
}

void automatic_dosing_callback(void* ptr)
{

}




void default_operation(void)
{

}



// NEXTION BUTTON CALLBACKS

void btn_calib1_POP_callback(void* ptr)  
{
    eeprm.get_configuration(&cfgOnEdit, 1);
    cfgOnEdit.id = 1;
    //callibrate_by_time_callback(nullptr);
}
void btn_calib2_POP_callback(void* ptr)  
{
    eeprm.get_configuration(&cfgOnEdit, 2);
    cfgOnEdit.id = 2;
    //callibrate_by_time_callback(nullptr);
}  
void btn_calib3_POP_callback(void* ptr)  
{
    eeprm.get_configuration(&cfgOnEdit, 3);
    cfgOnEdit.id = 3;
    //callibrate_by_time_callback(nullptr);
}  
void btn_calib4_POP_callback(void* ptr)  
{
    eeprm.get_configuration(&cfgOnEdit, 4);
    cfgOnEdit.id = 4;
    //callibrate_by_time_callback(nullptr);
}  
void btn_calib5_POP_callback(void* ptr)  
{
    eeprm.get_configuration(&cfgOnEdit, 5);
    cfgOnEdit.id = 5;
    //callibrate_by_time_callback(nullptr);
    
}
//TODO - 
void save_calib_callback(void* ptr)
{
    end_callibration();
}

void chk1_callback(void* ptr)
{
    auto chk = reinterpret_cast<NexCheckbox*>(ptr);
    eeprm.get_configuration(&cfgOnEdit, 1);
    doser.configure(cfgOnEdit);
}

void chk2_callback(void* ptr)
{
    auto chk = reinterpret_cast<NexCheckbox*>(ptr);
    eeprm.get_configuration(&cfgOnEdit, 2);
    doser.configure(cfgOnEdit);
}

void chk3_callback(void* ptr)
{
    auto chk = reinterpret_cast<NexCheckbox*>(ptr);
    eeprm.get_configuration(&cfgOnEdit, 3);
    doser.configure(cfgOnEdit);
}

void chk4_callback(void* ptr)
{
    auto chk = reinterpret_cast<NexCheckbox*>(ptr);
    eeprm.get_configuration(&cfgOnEdit, 4);
    doser.configure(cfgOnEdit);
}

void chk5_callback(void* ptr)
{
    auto chk = reinterpret_cast<NexCheckbox*>(ptr);
    eeprm.get_configuration(&cfgOnEdit, 5);
    doser.configure(cfgOnEdit);
}

// press until pipe fills
void btn_pipe_filling_POP_callback(void* ptr)  
{
    state::dosing_manual = true;
    doser.setMode(DosingMode::Manual);
    set_pedal_callbacks_todefault();
}
void btn_start_pedal_filling_POP_callback(void* ptr)  
{

}
void btn_pipe_filling2_POP_callback(void* ptr)  
{
    pedal_callback = automatic_dosing_callback;
}   
  
void btn_start_auto_filling_POP_callback(void* ptr)  
{
    static char buf[10] = {0};
    txt_fill_amount.getText(buf, 10);
    state::remaining_to_dose =  atoi(buf);
    state::remaining_to_dose--;
    state::dosing_manual = false;
    //TODO - seconds or milliseconds ? 
    txt_delay.getText(buf, 10);
    state::delay_between_fills = atoi(buf);
    state::delay_between_fills *= 100;
    doser.setMode(DosingMode::Auto);
    state::last_fill_time = millis();
    state::operation = auto_fill;
    //pedal_callback = automatic_dosing_pedal_callback;

}

void auto_fill(void)
{
    static char buf[10] = {0};
    if(millis() - state::last_fill_time > state::delay_between_fills)
    {
        if(!(state::remaining_to_dose == NOTHING_TO_DOSE) && !doser.isDosing())
        {
            doser.dose();
            state::remaining_to_dose--;
        }
        itoa(state::remaining_to_dose +1, buf, 3);
        txt_fill_amount.setText(buf);
    }

}

void btn_stop_pedal_POP_callback(void* ptr)  
{
 
}

void btn_save_calib_callback(void* ptr)
{
    end_callibration(nullptr);
}

void proceed_to_filling(void* ptr)
{

}

void btn_fill_by_foot_callback(void* ptr)
{
    state::dosing_manual = true;
    set_pedal_callbacks_todefault();
}

void btn_numpad_ok_callback(void* ptr)
{
    static char buf[10];
    txt_numpad.getText(buf,10);
    *state::keyboard_target = atoi(buf);
    
}

void txt_pipe_r_callback(void* ptr)
{
    state::keyboard_target = &(cfgOnEdit.pipe_radius);
}

void txt_fill_amount_callback(void* ptr)
{
     state::keyboard_target = &(state::fill_amount);
}

void txt_delay_callback(void* ptr);
{
    state::keyboard_target = &state::delay_between_fills;
}