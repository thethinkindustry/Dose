#ifndef _StepMotorDriver_
#define _StepMotorDriver_

enum StepDirection
{
    Left = 0,
    Right = 1
};

class StepMotor
{
    public:
   
    void virtual setRPM(int rpm) = 0;
    void virtual run() = 0;
    void virtual stop() = 0;
    void virtual setDirection(StepDirection dir) = 0;
    void virtual setPulse(int p) = 0;
    StepDirection getDirection();
    int getRPM();
    bool isActive();



    protected:
    StepDirection direction;
    bool active;
    int pulse;
    int rpm;
};

#endif 