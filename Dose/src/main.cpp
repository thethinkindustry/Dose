#ifdef ARDUINO
#include <Arduino.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>
#include <StaticTimer.h>
typedef AVR_StepMotor StepMotorBase;
#endif







void ftest(void* data)
{
  
  auto val = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN,!val);
}

void updateButtons(void*)
{
  for(int i = 0; i< AVR_Button::total(); i++)
  {
    auto button = AVR_Button::getButtons()[i];
    int state = digitalRead(button->uno_pin);
    button->update(state);
  }
}

int main() {

  
  AVR_Button button1(13);
  button1.addPressTask(ftest);

  pinMode(LED_BUILTIN, OUTPUT);
  AVR_StepMotor motor(0,0,0);

  
  motor.setDirection(StepDirection::Right);
  motor.setRPM(200);
  motor.setPulse(1800);
  motor.start();
  _delay_ms(3000);
  motor.stop();

  StaticTimer timer1(400);
  timer1.addTask(ftest);


  StaticTimer timer2(20);
  timer2.addTask(updateButtons);

  while(1)
  {
    timer1.update(millis());
    timer2.update(millis());
    motor.run();

  }

  

}

