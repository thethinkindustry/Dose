#include "StepMotorDriver.h"

StepDirection StepMotorDriver::getDirection()
{
    return direction;
}

int StepMotorDriver::getRPM()
{
    return rpm;
}

bool StepMotorDriver::isActive()
{
    return active;
}


