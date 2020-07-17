#ifdef ARDUINO
#include <Arduino.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>
#include <DosingController.h>
#include <EEPROMController.h>
typedef AVR_StepMotor StepMotorBase;
#endif

#include <globals.h>
#include <program.h>
#include <ITEADLIB_Arduino_Nextion/Nextion.h>

#define PUL_PIN 11
#define DIR_PIN 12
#define EN_PIN 13 

AVR_StepMotor motor = AVR_StepMotor(PUL_PIN,DIR_PIN, EN_PIN);
AVR_Button pedal = AVR_Button(7);
DosingController doser = DosingController(&motor);
//EEPROMController eeprom = EEPROMController(1024);
ButtonFunc pedal_callback = default_pedal_callback;
ButtonFunc pedal_release_callback = default_pedal_release_callback;

void ftest(void* data)
{
  
  Serial.println("button");
  if(!motor.isActive())
  {
    motor.start();
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    motor.stop();
  }

}

void ftest_release(void* d)
{
  Serial.println("released");
}

void setup()
{
  set_pedal_callbacks_todefault();
  pedal_callback = ftest;
  pedal_release_callback = ftest_release;
  doser = DosingController(&motor);
  doser.configure(DosingConfiguration());

  pinMode(LED_BUILTIN, OUTPUT);
  pedal.setMode(ButtonMode::PullDown);
  pedal.setDebounceDeadtime(100);
  pedal.addPressTask(pedal_callback);
  pedal.addReleaseTask(pedal_release_callback);

  Serial.begin(9600);
  motor.setRPM(100);
  motor.stop();
}

void loop()
{

  AVR_Button::updateButtons(millis());
  doser.run(micros());
  (*state::operation)(nullptr);

}


