#include "AVR_StepMotor.h"

#ifndef TESTING_NATIVE

AVR_StepMotor::AVR_StepMotor()
{
    active = false;
    direction = StepDirection::Right;
    rpm = 500;
    pulse = 200;
}

AVR_StepMotor::AVR_StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin)
{

    active = false;
    direction = StepDirection::Right;
    rpm = 500;
    pulse = 200;
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

void AVR_StepMotor::setPulse(int p)
{
   pulse=p;
   setRPM_t();
}
void AVR_StepMotor::set(StepDirection _dir, uint8_t _rpm, uint16_t _pulse){
    direction = _dir;
    rpm = _rpm;
    pulse = _pulse;
    setRPM_t();
}

void AVR_StepMotor::stop()
{
     active = false;
    digitalWrite(enPin, active);
}


void AVR_StepMotor::run()
{ 
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(rpm_t);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(rpm_t);
}



#endif
