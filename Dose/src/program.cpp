#include <ITEADLIB_Arduino_Nextion/Nextion.h>
#include <globals.h>
#include <program.h>
#include <string.h>
void init_nextion_buttons()
{

}
void select_config(void* ptr)
{
    //TODO- get configs from eeprom
    //TODO- write configs to screen


    
}

void dose_callback(void* ptr)
{

}

void callibrate_by_time_callback(void* ptr)
{
    state::operation = callibrate_by_time;
    pedal_callback = pedal_callibrate_by_time;
    state::last_total_steps = motor.getTotalSteps();
    state::last_ticks_us = micros();
}

void save_config_callback(void* ptr)
{
    //TODO - set cfgOnEdit id based on config button
    save_current_config();
}

void save_current_config(void)
{
    eeprm.save_configuration(cfgOnEdit);
}

void save_config_on_edit(void)
{

}

void callibrate_by_time(void* d)
{
    auto state = pedal.checkState();
    if(state == ButtonState::Pressed && motor.isActive())
    {
    }
}

void pedal_callibrate_by_time(void* d)
{

    
}

void end_callibration()
{
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
    if(!(state::remaining_to_dose == NOTHING_TO_DOSE) && !doser.isDosing())
    {
        doser.dose();
        state::remaining_to_dose--;
    }
    //TODO- update the textbox with remaining_to_dose + 1

    static char buf[10];
    itoa(state::remaining_to_dose+1, buf,3);
    //TODO- update the textbox
    
}

void automatic_dosing_at_exit(void* ptr)
{
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
    //TODO- get how many times to dose from textbox - 1
    state::remaining_to_dose = 0;
    state::dosing_manual = false;
    doser.setMode(DosingMode::Auto);
    pedal_callback = automatic_dosing_pedal_callback;
}

void default_operation(void* ptr)
{

}
