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
    rpm_t = 60000000 / 2 / steps / rpm;
}

int StepMotor::getSteps()
{
    return steps;
}

uint64_t StepMotor::getTotalSteps()
{
    return total_steps;
}


bool StepMotor::isActive()
{
    return active;
}


