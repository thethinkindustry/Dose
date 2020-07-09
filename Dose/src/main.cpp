//#ifndef UNIT_TEST
#include <Arduino.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>
typedef AVR_StepMotor StepMotorBase;
#ifdef ARDUINO

#endif

AVR_Button* button = nullptr;

void* ftest(void* data)
{
  digitalWrite(13, HIGH);
  _delay_ms(500);
  digitalWrite(13, LOW);
  _delay_ms(500);
}

void setup() {

  pinMode(13, OUTPUT);
  AVR_StepMotor motor(0,0,0);
  
  motor.setDirection(StepDirection::Right);
  motor.setRPM(200);
  motor.setPulse(1800);
  motor.start();
  _delay_ms(3000);
  motor.stop();

  button = new AVR_Button();
  ButtonFunc f(ftest);
  button->addPressTask(&f);

  

}

void loop() {
  _delay_ms(1000);
  button->update();
}

//#endif // UNIT_TEST