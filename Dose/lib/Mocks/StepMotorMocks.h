#include <stdint.h>
#include <StepMotor.h>

#ifndef _StepMotorMocks_
#define _StepMotorMocks_

class StepMotorMock : public StepMotor
{
    public:
    StepMotorMock();
    StepMotorMock(uint8_t enPin, uint8_t dirPin, uint8_t stepPin);
    void setRPM(int rpm);
    void stop();
    void run();
    void setDirection(StepDirection dir);
    void setPulse(int p);
};

#endif


