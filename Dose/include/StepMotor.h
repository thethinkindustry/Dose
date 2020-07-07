#ifndef _StepMotor_
#define _StepMotor_

#ifdef ARDUINO 
#include "AVR_StepMotor.h"
typedef AVR_StepMotor StepMotorBase;
#endif


class StepMotor: public StepMotorBase
{

    public:
    StepMotor();
    StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin);
};

#endif