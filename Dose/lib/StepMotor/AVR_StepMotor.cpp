#include "AVR_StepMotor.h"

#ifndef TESTING_NATIVE

AVR_StepMotor::AVR_StepMotor()
{
    active = false;
    direction = StepDirection::Right;
    rpm = 200;
    steps = 1600;
    last_ticks = 0;
    setRPM(rpm);
    pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enPin, OUTPUT);
}

AVR_StepMotor::AVR_StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin)
{

    active = false;
    direction = StepDirection::Right;
    rpm = 200;
    steps = 1600;
    last_ticks = 0;
    total_steps = 0;
    setRPM(rpm);
    enPin = _enPin;
    dirPin = _dirPin;
    stepPin = _stepPin;
    pinMode(_stepPin, OUTPUT);
	pinMode(_dirPin, OUTPUT);
	pinMode(_enPin, OUTPUT);

    digitalWrite(dirPin, LOW);
	stop();
}

inline void AVR_StepMotor::start()
{
    active = true;
    digitalWrite(enPin, HIGH);
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
    digitalWrite(enPin, LOW);
}


void AVR_StepMotor::run(uint64_t ticks_us)
{ 
    if(!active) {
        return;
    }
   // if(active == true){
      //  return;
    //}
    //if(step_pin_state != 1 &&  ((ticks_us - last_ticks) >= rpm_t))
    //{
        
        digitalWrite(stepPin, HIGH);
        step_pin_state = 1;
        last_ticks = ticks_us;
        delayMicroseconds(rpm_t);
    //}

    //else if(step_pin_state != 0 && ((ticks_us - last_ticks) >= rpm_t))
    //{
        
        digitalWrite(stepPin, LOW);
        step_pin_state = 0;
        last_ticks = ticks_us;
        //total_steps++;
        delayMicroseconds(rpm_t);
        total_steps++;
        /*
        if(active) {
            total_steps++;
        }
        */
    //}
    //}
}



#endif
