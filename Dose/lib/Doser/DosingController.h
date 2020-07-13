/**
 * @file DosingController.h
 * @author koray ilbuga (koray0199@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _DosingController_
#define _DosingController_
#include <StepMotor.h>

class DosingConfiguration
{
    private:
    int volumePerSec;
    int stepPerUnit;

    public:
    DosingConfiguration();
    void setSpeed(int vol);
    static DosingConfiguration createDefault();


};

/**
 * @brief Takes control of the motor and performs reliable dosing according
 * to taken configuration.
 * 
 */
class DosingController
{
    private:
    StepMotor* motor;
    DosingConfiguration config;
    bool dosing;
    DosingController();
    public:
    DosingController(StepMotor* motor);
    void configure(DosingConfiguration cfg);
    bool isDosing();
    void dose();
    /**
     * @brief Needs to be called in main program loop
     * 
     * @param ticks 
     */
    void run(unsigned long ticks);

};

#endif