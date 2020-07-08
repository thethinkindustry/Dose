#include "StepMotor.h"

StepDirection StepMotor::getDirection()
{
    return direction;
}

int StepMotor::getRPM()
{
    return rpm;
}

bool StepMotor::isActive()
{
    return active;
}


