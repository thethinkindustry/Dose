#include "AVR_StepMotor.h"


AVR_StepMotor::AVR_StepMotor()
{
    active = false;
    direction = StepDirection::Right;
    rpm = 0;
    pulse = 0;
}

AVR_StepMotor::AVR_StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin)
{
    driver = MWCSTEPPER( _enPin, _dirPin, _stepPin);
    driver.init();
    active = false;
    direction = StepDirection::Right;
    rpm = 0;
    pulse = 0;
}

void AVR_StepMotor::stop()
{
    driver.active(false);
    active = false;
}

void AVR_StepMotor::setRPM(int rpm)
{
    this->rpm = rpm;
    driver.set(direction, rpm, pulse);
}

void AVR_StepMotor::run()
{
    driver.active(true);
    driver.run();
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

