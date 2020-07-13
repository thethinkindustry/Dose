#include <DosingController.h>

DosingConfiguration::DosingConfiguration()
{

}

void DosingConfiguration::setSpeed(int vol)
{
    volumePerSec = vol;
}

DosingConfiguration DosingConfiguration::createDefault()
{
    DosingConfiguration cfg;
    cfg.stepPerUnit = 0;
    cfg.volumePerSec = 0;
    return cfg;
}

DosingController::DosingController()
:motor{nullptr}, dosing{false}
{

}

DosingController::DosingController(StepMotor* motor)
:motor{motor}, dosing{false}
{

}

void DosingController::configure(DosingConfiguration cfg)
{
    config = cfg;
}

bool DosingController::isDosing()
{
    return dosing;
}

void DosingController::dose()
{
    if(motor == nullptr || dosing) return;
    dosing = true;

}

void DosingController::run(unsigned long ticks)
{
    motor->run();
}