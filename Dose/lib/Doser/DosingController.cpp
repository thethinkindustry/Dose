#include <DosingController.h>
#include <Arduino.h>

DosingConfiguration::DosingConfiguration()
:id{0}, volume{0}, pipe_radius{0}, volumePerSec{0}, stepPerUnit{0}, motor_steps{0},
work_time{0}, steps_to_run{0}, checksum{0}
{

}

DosingController::DosingController()
:motor{nullptr}, dosing{false}
{

}

DosingController::DosingController(StepMotor* motor)
:motor{motor}, dosing{false}, mode{DosingMode::Manual}
{
    last_steps_runned = motor->getTotalSteps();
}

void DosingController::configure(DosingConfiguration cfg)
{
    config = cfg;
    configureMotor();
}

void DosingController::configureMotor()
{
    if(motor == nullptr) return;
    motor->setRPM(config.motor_rpm);
    motor->setSteps(config.motor_steps);
    last_steps_runned = motor->getTotalSteps();

}


bool DosingController::isDosing()
{
    return dosing;
}

void DosingController::setMode(DosingMode m)
{
    mode = m;
    last_steps_runned = motor->getTotalSteps();
}

void DosingController::dose()
{
    //if(motor == nullptr || dosing == true) return;
    dosing = true;
    motor->start();

}

DosingConfiguration DosingController::getConfig()
{
    return config;
}


//TODO- Reconfigure configuration according to new RPM
void DosingController::setRPM(int rpm)
{
    motor->setRPM(rpm);

}

void DosingController::stop(void)
{
    dosing = false;
    motor->stop();
    last_steps_runned = motor->getTotalSteps();
    
}

void DosingController::run(uint64_t ticks)
{
    //motor->run(ticks);
    //if(mode == DosingMode::Auto && (motor->getTotalSteps() - last_steps_runned >= config.steps_to_run))
    //static auto motor_total_steps = motor->getTotalSteps();
    
    if(mode == DosingMode::Auto) 
    {
        if((motor->getTotalSteps() - last_steps_runned) >= config.steps_to_run)
        {
            stop();
            Serial.println("stopped");
            
        }
        else
        {
            motor->run(ticks);
        }
        
    }
    /*
    if(mode == DosingMode::Auto && ((motor_total_steps - last_steps_runned) >= config.steps_to_run))
    {
        stop();
        last_steps_runned = motor_total_steps;
    }
    */
    
}

