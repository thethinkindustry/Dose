#include <StepMotorMock.h>



StepMotorMock::StepMotorMock()
{
    
    active = false;
    direction = StepDirection::Left;
    rpm = 0;
    steps = 0;
}

StepMotorMock::StepMotorMock(uint8_t enPin, uint8_t dirPin, uint8_t stepPin)
{
    active = false;
    direction = StepDirection::Left;
    rpm = 0;
    steps = 0;
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

void StepMotorMock::run(unsigned long ticks_us)
{
    

}
void StepMotorMock::setSteps(int p)
{
    steps= p;
}

void StepMotorMock::start()
{
    active = true;
}