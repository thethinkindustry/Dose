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
    uint8_t id;
    uint32_t pipe_radius;
    uint16_t volume;
    uint16_t volumePerSec;
    uint32_t stepPerUnit;
    uint16_t motor_steps;
    uint16_t motor_rpm;
    uint64_t work_time;
    uint64_t steps_to_run;
    uint8_t checksum;

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