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
    driver = MWCSTEPPER( _enPin, _dirPin, _stepPin);
    driver.init();
    active = false;
    direction = StepDirection::Right;
    rpm = 500;
    pulse = 200;
    setRPM(rpm);
}

inline void AVR_StepMotor::start()
{
    active = true;
    digitalWrite(enPin, active);
}
void AVR_StepMotor::setRPM(int _rpm)
{
    rpm = _rpm;
    rpm_t = 60000000 / 2 / _pulse / _rpm;
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

void AVR_StepMotor::setDirection(StepDirection dir)
{
    direction = dir;
    driver.set(direction, rpm, pulse);

}

void AVR_StepMotor::setPulse(int p)
{
    pulse = p;
    driver.set(direction, rpm, pulse);
}

#endif
