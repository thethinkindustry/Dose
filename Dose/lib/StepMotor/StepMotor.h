#ifndef _StepMotor_
#define _StepMotor_

#include <stdint.h>

enum StepDirection
{
    Left = 0,
    Right = 1
};

class StepMotor
{
    public:
    virtual void  setRPM(int rpm) = 0;
    virtual void  start() = 0;
    virtual void  stop() = 0;
    virtual void  setDirection(StepDirection dir) = 0;
    virtual void  setPulse(int p) = 0;
    StepDirection getDirection();
    int getRPM();
    bool isActive();

    protected:
    StepDirection direction;
    bool active;
    uint8_t pulse;
    uint8_t rpm;
    uint8_t rpm_t;
};

#endif 