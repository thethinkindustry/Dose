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

enum DosingMode
{
    Manual,
    Auto
};

struct DosingConfiguration
{
    uint8_t id = 0;
    uint32_t pipe_radius = 0;
    uint16_t volume  = 0;
    uint16_t motor_steps = 0;
    uint16_t motor_rpm = 300;
    uint64_t steps_to_run = 1600;
    uint8_t checksum = 0;

    DosingConfiguration();
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
    uint64_t last_steps_runned;
    DosingMode mode;
    DosingController();

    void configureMotor();
    public:
    DosingController(StepMotor* motor);
    DosingConfiguration getConfig();
    void configure(DosingConfiguration cfg);
    void setRPM(int rpm);
    bool isDosing();
    void dose();
    void stop(void);
    void setMode(DosingMode m);
    /**
     * @brief Needs to be called in main program loop
     * 
     * @param ticks 
     */
    void run(uint64_t ticks);



};

#endif