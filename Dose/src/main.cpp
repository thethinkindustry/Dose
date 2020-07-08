#include <Arduino.h>
#include <AVR_StepMotor.h>


#ifndef UNIT_TEST

#ifdef ARDUINO 
typedef AVR_StepMotor StepMotorBase;
#endif

void setup() {
  StepMotor* motor = new StepMotorBase(0,0,0);
  motor->setDirection(StepDirection::Right);
  motor->setRPM(200);
  motor->setPulse(1800);
  motor->run();
  _delay_ms(3000);
  motor->stop();

}

void loop() {
  // put your main code here, to run repeatedly:
}

#endif