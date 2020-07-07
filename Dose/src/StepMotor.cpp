#include "StepMotor.h"

StepMotor::StepMotor()
{

}

StepMotor::StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin)
:StepMotorBase(_enPin, _dirPin, _stepPin)
{
    
}