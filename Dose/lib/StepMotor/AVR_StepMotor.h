#ifndef _AVR_StepMotor_
#define _AVR_StepMotor_

#include <StepMotor.h>
#ifndef TESTING_NATIVE
#include "mwc_stepper.h"



class AVR_StepMotor: public StepMotor
{
    private:
	uint8_t enPin;
	uint8_t stepPin;
	uint8_t dirPin;
    void run();
    public:
    AVR_StepMotor();
    AVR_StepMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin);
    void stop();
    void start();
    void setDirection(StepDirection dir);
    void setPulse(int p);
    void setRPM(int rpm);
    void set(bool _dir, uint8_t _rpm, uint16_t _pulse);
};

#endif
#endif