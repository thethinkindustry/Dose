#include "StepMotor.h"
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