#include "AVR_StepMotor.h"

#ifndef TESTING_NATIVE

AVR_StepMotor::AVR_StepMotor()
{
    active = false;
    direction = StepDirection::Right;
    rpm = 500;
    steps = 200;
    last_ticks = 0;
}

AVR_StepMotor::AVR_StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin)
{

    active = false;
    direction = StepDirection::Right;
    rpm = 500;
    steps = 200;
    last_ticks = 0;
    setRPM(rpm);
    pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enPin, OUTPUT);
	digitalWrite(enPin, LOW);
}

inline void AVR_StepMotor::start()
{
    active = true;
    digitalWrite(enPin, active);
}
void AVR_StepMotor::setRPM(int _rpm)
{
    rpm = _rpm;
    setRPM_t();
    
}

//TODO- change motor direction while running
void AVR_StepMotor::setDirection(StepDirection dir)
{
    direction = dir;
}

void AVR_StepMotor::setSteps(int s)
{
   steps = s;
   setRPM_t();
}
void AVR_StepMotor::set(StepDirection _dir, uint8_t _rpm, uint16_t _steps){
    direction = _dir;
    rpm = _rpm;
    steps = _steps;
    setRPM_t();
}

void AVR_StepMotor::stop()
{
     active = false;
    digitalWrite(enPin, active);
}


void AVR_StepMotor::run(unsigned long ticks_us)
{ 

    if(step_pin_state != 1 &&  ticks_us - last_ticks >= rpm_t)
    {
        digitalWrite(stepPin, HIGH);
        step_pin_state = 1;
        last_ticks = ticks_us;
    }

    else if(step_pin_state != 0 && ticks_us - last_ticks >= rpm_t)
    {
        digitalWrite(stepPin, LOW);
        step_pin_state = 0;
        last_ticks = ticks_us;
        total_steps++;
    }



}



#endif
