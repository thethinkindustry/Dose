#include <StepMotorMock.h>



StepMotorMock::StepMotorMock()
{
    
    active = false;
    direction = StepDirection::Left;
    rpm = 0;
    pulse = 0;
}

StepMotorMock::StepMotorMock(uint8_t enPin, uint8_t dirPin, uint8_t stepPin)
{
    active = false;
    direction = StepDirection::Left;
    rpm = 0;
    pulse = 0;
}

void StepMotorMock::setDirection(StepDirection dir)
{
    direction = dir;
}

void StepMotorMock::setRPM(int rpm)
{
    this->rpm = rpm;
}

void StepMotorMock::stop()
{
    active = false;
}

void StepMotorMock::run()
{
    active = true;

}
void StepMotorMock::setPulse(int p)
{
    this->pulse = p;
}

void StepMotorMock::start()
{
    active = true;
}