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
  Serial.println("ledtest");

}

void ftest2(void* data)
{
  
  auto val = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN,!val);
  Serial.println("released");

}



int main() {

  pinMode(LED_BUILTIN, OUTPUT);
  AVR_Button button1(12);
  button1.addPressTask(ftest);
  button1.addReleaseTask(ftest2);
  
  AVR_Button button2(10);
  

  StaticTimer timer1(400);
  timer1.addTask(ftest);


  //StaticTimer timer2(20);
  //timer2.addTask(AVR_Button::updateButtons);
  Serial.begin(9600);

  while(1)
  {
    AVR_Button::updateButtons(nullptr);
    //timer1.update(millis());
    //timer2.update(millis());
    //motor.run();
    //Serial.println("asd");

  }

  

}

