
#include <globals.h>
#include <program.h>
#include <string.h>

void nextion_callback_setup(void){
    pedal_filling_btn.attachPush(pedal_filling_callback);
    //auto_filling_btn.attachPush(auto_filling_callback);
    calib1_btn.attachPush(calib1_btn_callback);
    calib2_btn.attachPush(calib2_btn_callback);
    calib3_btn.attachPush(calib3_btn_callback);
    calib4_btn.attachPush(calib4_btn_callback);
    calib5_btn.attachPush(calib5_btn_callback);
    chk1.attachPush(chk1_callback);
    chk2.attachPush(chk2_callback);
    chk3.attachPush(chk3_callback);
    chk4.attachPush(chk4_callback);
    chk5.attachPush(chk5_callback);
    calib_continue_btn.attachPush(calib_continue_callback);
    //calib_radius_txt.attachPop(calib_radius_callback);
    //calib_volume_txt.attachPop(calib_volume_callback);
    calib_complete_btn.attachPush(calib_complete_callback);
    end_fill_btn.attachPush(end_fill_callback);
    //left_to_fill_txt.attachPop(left_to_fill_callback);

    press_until_pipe_fills_btn.attachPush(press_until_pipe_fills_press_callback);
    press_until_pipe_fills_btn.attachPop(press_until_pipe_fills_release_callback);
    start_fill_btn.attachPush(start_fill_callback);
    auto_fill_start_btn.attachPush(auto_fill_start_callback);
    //ok_btn.attachPush(ok_btn_callback);
    setting_rpm_slider.attachPop(rpm_slider_callback);
}

void pedal_filling_callback(void* ptr)
{
    state::mode = ProgramMode::Manual;
}

void auto_filling_callback(void* ptr)
{
    state::remaining_to_fill = 200;
    state::operation = config_auto_operation;
    
}

void calib1_btn_callback(void* ptr)
{
    uint8_t id = 0;

    eeprm.get_configuration(&current_cfg, id);
    uint32_t val = 0;
    setting_rpm_slider.getValue(&val);
    current_cfg.motor_rpm = val;
    calib_radius_txt.setValue(current_cfg.pipe_radius);
    calib_volume_txt.setValue(current_cfg.volume);
    //state::operation = config_operation;
    
}

void calib2_btn_callback(void* ptr)
{
    uint8_t id = 1;
    uint32_t val = 0;
    eeprm.get_configuration(&current_cfg, id);
    setting_rpm_slider.getValue(&val);
    current_cfg.motor_rpm = val;
    calib_radius_txt.setValue(current_cfg.pipe_radius);
    calib_volume_txt.setValue(current_cfg.volume);
    //state::operation = config_operation;
}

void calib3_btn_callback(void * ptr)
{
    uint8_t id = 2;
    eeprm.get_configuration(&current_cfg, id);
    uint32_t val = 0;
    setting_rpm_slider.getValue(&val);
    current_cfg.motor_rpm = val;
    calib_radius_txt.setValue(current_cfg.pipe_radius);
    calib_volume_txt.setValue(current_cfg.volume);
    //state::operation = config_operation;
}

void calib4_btn_callback(void * ptr)
{
    uint8_t id = 3;
    eeprm.get_configuration(&current_cfg, id);
    uint32_t val = 0;
    setting_rpm_slider.getValue(&val);
    current_cfg.motor_rpm = val;
    calib_radius_txt.setValue(current_cfg.pipe_radius);
    calib_volume_txt.setValue(current_cfg.volume); 
    //state::operation = config_operation;
}

void calib5_btn_callback(void * ptr)
{
    uint8_t id = 4;
    eeprm.get_configuration(&current_cfg, id);
    uint32_t val = 0;
    while(!setting_rpm_slider.getValue(&val));
    current_cfg.motor_rpm = val;
    while(!calib_radius_txt.setValue(current_cfg.pipe_radius));
    while(!calib_volume_txt.setValue(current_cfg.volume));
    //state::operation = config_operation;
}

void chk1_callback(void* ptr)
{
    uint8_t id = 0;
    eeprm.get_configuration(&current_cfg, id);
    doser.configure(current_cfg);
    
}

void chk2_callback(void* ptr)
{
    uint8_t id = 1;
    eeprm.get_configuration(&current_cfg, id);
    doser.configure(current_cfg);
}

void chk3_callback(void* ptr)
{
    uint8_t id = 2;
    eeprm.get_configuration(&current_cfg, id);
    doser.configure(current_cfg);
}

void chk4_callback(void* ptr)
{
    uint8_t id = 3;
    eeprm.get_configuration(&current_cfg, id);
    doser.configure(current_cfg);
}

void chk5_callback(void* ptr)
{
    uint8_t id = 4;
    eeprm.get_configuration(&current_cfg, id);
    doser.configure(current_cfg);    
}

void calib_continue_callback(void* ptr)
{
    //eeprm.save_configuration(current_cfg);
    uint32_t val = 0;
    state::mode = ProgramMode::Callibration;
    //state::operation = nullptr;
    

    while(!calib_radius_txt.getValue(&val));
    current_cfg.pipe_radius = val;
    while(!calib_volume_txt.getValue(&val));
    current_cfg.volume = val;
    //page_pipe.show();
}

/*
void calib_radius_callback(void* ptr)
{
   
    state::numpad_mode = NumpadMode::calib_radius;
    //current_cfg.volume = 999;
    //_volume.setValue(999);
    //calib_volume_txt.setValue(current_cfg.volume);
}

void calib_volume_callback(void* ptr)
{
    
    state::numpad_mode = NumpadMode::calib_volume;
}
*/
void calib_complete_callback(void* ptr)
{
    pedal_callback = pedal_empty_callback;
    pedal_release_callback = pedal_empty_callback;
    state::mode = ProgramMode::Auto;
    current_cfg.steps_to_run = motor.getTotalSteps() - state::steps_before_callibration;
    //current_cfg.steps_to_run = state::callibration_steps;
    eeprm.save_configuration(current_cfg);
    doser.configure(current_cfg);
    read_callibrations();
}

void press_until_pipe_fills_press_callback(void* ptr)
{
    //doser.setMode(DosingMode::Manual);
    //motor.setRPM(200);
    //motor.start();
    doser.setMode(DosingMode::Manual);
    doser.dose();
}

void press_until_pipe_fills_release_callback(void* ptr)
{
    doser.stop();
}

void left_to_fill_callback(void* ptr)
{
    //state::numpad_target = left_to_fill_txt;
    //state::numpad_mode = NumpadMode::left_to_fill;
}

void start_fill_callback(void* ptr)
{
    if(state::mode == ProgramMode::Callibration)
    {
        doser.setMode(DosingMode::Manual);
        //motor.setRPM(200);
        //current_cfg.motor_rpm = 200;
        //doser.configure(current_cfg);
        state::last_total_steps = motor.getTotalSteps();
        state::callibration_steps = 0;
        state::steps_before_callibration = motor.getTotalSteps();
        //pedal_callback = pedal_callibration_press_callback;
        //pedal_release_callback = pedal_callibration_release_callback;
        pedal_callback = pedal_default_fill_callback;
        pedal_release_callback = pedal_default_fill_release_callback;
    }

    else if(state::mode == ProgramMode::Manual)
    {
        doser.setMode(DosingMode::Auto);
        pedal_callback = pedal_default_fill_callback;
        pedal_release_callback = pedal_empty_callback;
        state::operation = nullptr;
        //pedal_release_callback = pedal_default_fill_release_callback;
    }
    
    else if(state::mode == ProgramMode::Auto)
    {
        doser.setMode(DosingMode::Auto);
        doser.configure(current_cfg);
        uint32_t val = 0;
        while(!auto_to_fill_txt.getValue(&val));
        while(!left_to_fill_txt.setValue(val));
        while(!auto_wait_time_txt.getValue(&val));
        state::delay_between_fills = val;
        state::operation = auto_operation;
        state::remaining_to_fill--;
        doser.dose();
    }
}

void end_fill_callback(void* ptr)
{
    doser.stop();
    state::operation = nullptr;
}


//TODO add end filling button
//TODO
void auto_fill_start_callback(void* ptr)
{
    state::mode = ProgramMode::Auto;
    doser.setMode(DosingMode::Auto);

    pedal_callback = pedal_empty_callback;
    state::auto_last_fill_ticks = millis();
    state::operation = nullptr;
    uint32_t val = 0; 
    while(!auto_to_fill_txt.getValue(&val));
    
    state::remaining_to_fill = val;
    while(!auto_wait_time_txt.getValue(&val));
    state::delay_between_fills = val;
    
}

void ok_btn_callback(void* ptr)
{
    uint32_t val = 0;
    //input_txt.getText(state::txt_buf, 16);
    //state::numpad_target.setText(state::txt_buf);
    switch (state::numpad_mode)
    {
    case NumpadMode::left_to_fill :
        //state::remaining_to_fill = atoi(state::txt_buf);
        break;
    
    case NumpadMode::calib_radius :
        //current_cfg.pipe_radius = atoi(state::txt_buf);
       // calib_radius_txt.getValue(&val);
       // current_cfg.pipe_radius = val;
        break;
    
    case NumpadMode::calib_volume :
        //current_cfg.volume = atoi(state::txt_buf);

       // calib_volume_txt.getValue(&val);
       // current_cfg.volume = val;
        break;

    default:
        break;
    }
    state::numpad_mode = NumpadMode::none;
}

void rpm_slider_callback(void* ptr)
{
    uint32_t val = 0;
    setting_rpm_slider.getValue(&val);
    current_cfg.motor_rpm = val;
}

// OPERATIONS
void callibrate_operation(void)
{

}

void auto_operation(void)
{

    if(state::remaining_to_fill > 0)
    {
        if(!state::dosed && state::auto_last_state == true && !doser.isDosing())
        {
            state::auto_last_fill_ticks = millis();
            state::dosed = true;
        }

       if(state::dosed)
       {
           if(millis() - state::auto_last_fill_ticks > state::delay_between_fills)
           {
               state::dosed = false;
               state::remaining_to_fill--;
               while(!left_to_fill_txt.setValue(state::remaining_to_fill));
               doser.dose();
           }
       }
        
    }
    else
    {
        doser.stop();
    }
    
    state::auto_last_state = doser.isDosing();
}

void config_operation(void)
{
    uint32_t val = 0;
    calib_radius_txt.getValue(&val);
    current_cfg.pipe_radius = val;
    calib_volume_txt.getValue(&val);
    current_cfg.volume = val;
    return;

}

void config_auto_operation(void)
{
    /*
    uint32_t val = 100;
    auto_to_fill_txt.getValue(&val);
    state::remaining_to_fill = val;
    auto_wait_time_txt.getValue(&val);
    state::delay_between_fills = val;
    */
}

// PEDAL CALLBACKS
void pedal_callibration_press_callback(void*)
{
    //motor.start();
    doser.setMode(DosingMode::Manual);
    doser.dose();
}

void pedal_callibration_release_callback(void*)
{
    //motor.stop();
    doser.stop();
    state::callibration_steps += motor.getTotalSteps() - state::last_total_steps;
    state::last_total_steps = motor.getTotalSteps();
}

void pedal_empty_callback(void*)
{
    return;
}

void pedal_default_fill_callback(void*)
{
    /*
    if(state::remaining_to_fill)
    {
        doser.dose();
        state::remaining_to_fill--;
        itoa(state::remaining_to_fill, state::txt_buf, 3);
    }
    */
   //motor.start();
   doser.dose();
}

void pedal_default_fill_release_callback(void*)
{
    doser.stop();
    //motor.stop();
}

void pedal_auto_fill_callback(void*)
{

}



void read_callibrations()
{
    char* buf = state::txt_buf;
    DosingConfiguration cfg{};

    eeprm.get_configuration(&cfg, 0);
    snprintf(buf, 40, "Kal1 %10ld%10ld", cfg.pipe_radius, (uint32_t)cfg.volume);
    calib1_btn.setText(buf);

    eeprm.get_configuration(&cfg, 1);
    snprintf(buf, 40, "Kal2 %10ld%10ld", cfg.pipe_radius, (uint32_t)cfg.volume);
    calib2_btn.setText(buf);

    eeprm.get_configuration(&cfg, 2);
    snprintf(buf, 40, "Kal3 %10ld%10ld", cfg.pipe_radius, (uint32_t)cfg.volume);
    calib3_btn.setText(buf);

    eeprm.get_configuration(&cfg, 3);
    snprintf(buf, 40, "Kal4 %10ld%10ld", cfg.pipe_radius, (uint32_t)cfg.volume);
    calib4_btn.setText(buf);

    eeprm.get_configuration(&cfg, 4);
    snprintf(buf, 40, "Kal5 %10ld%10ld", cfg.pipe_radius, (uint32_t)cfg.volume);
    calib5_btn.setText(buf);
}


