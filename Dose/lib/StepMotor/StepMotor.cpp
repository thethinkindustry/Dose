#include "StepMotor.h"

StepDirection StepMotor::getDirection()
{
    return direction;
}

int StepMotor::getRPM()
{
    return rpm;
}

void StepMotor::setRPM_t()
{
    rpm_t = 60000000 / 2 / pulse / rpm;
}


bool StepMotor::isActive()
{
    return active;
}


