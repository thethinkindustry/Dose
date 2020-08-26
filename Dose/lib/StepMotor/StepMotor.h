/**
 * @file StepMotor.h
 * @author koray ilbuga (koray0199@gmail.com)
 * @brief Generic step motor class
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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
    virtual void  setSteps(int s) = 0;
    int getSteps();
    /**
     * @brief Needs to be called in main program loop as much as possible in
     * order to get a reliable operation.
     * 
     */
    virtual void  run(uint64_t ticks_us) = 0;
    uint64_t getTotalSteps();

    StepDirection getDirection();
    int getRPM();
    bool isActive();

    protected:
    void setRPM_t();
    StepDirection direction;
    bool active;
    uint16_t steps;
    uint16_t rpm;
    uint16_t rpm_t;
    uint64_t total_steps;
};

#endif 