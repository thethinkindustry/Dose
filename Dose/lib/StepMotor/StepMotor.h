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
    virtual void  setPulse(int p) = 0;
    /**
     * @brief Needs to be called in main program loop as much as possible in
     * order to get a reliable operation.
     * 
     */
    virtual void  run() = 0;
    void setRPM_t();
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