#ifndef _AVR_StepMotor_
#define _AVR_StepMotor_

#include <StepMotor.h>
#ifndef TESTING_NATIVE
#include "mwc_stepper.h"



class AVR_StepMotor: public StepMotor
{
    private:
    MWCSTEPPER driver;
    public:
    AVR_StepMotor();
    AVR_StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin);
    void setRPM(int rpm);
    void stop();
    void run();
    void setDirection(StepDirection dir);
    void setPulse(int p);

};

#endif
#endif