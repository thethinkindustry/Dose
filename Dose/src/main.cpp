#ifdef ARDUINO
#include <Arduino.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>
#include <DosingController.h>
#include <EEPROMController.h>
#include <mwc_stepper.h>
typedef AVR_StepMotor StepMotorBase;
#endif

#include <globals.h>
#include <program.h>
#include <Nextion.h>

//EEPROMController eeprom = EEPROMController(1024);
ButtonFunc pedal_callback = default_pedal_callback;
ButtonFunc pedal_release_callback = default_pedal_release_callback;
//MWCSTEPPER mwc = MWCSTEPPER(EN_PIN, DIR_PIN, PUL_PIN);


void ftest(void* data)
{
  /*
  if(!motor.isActive())
  {
    motor.start();
  }

  else
  {
    {
      motor.stop();
    }
  }
  */
  doser.dose();
  Serial.println("dosing");

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
  auto test_cfg = DosingConfiguration();
  test_cfg.motor_rpm = 400;
  test_cfg.motor_steps = 1600;
  test_cfg.steps_to_run = 3200;
  doser.configure(test_cfg);
  doser.setMode(DosingMode::Auto);

  pinMode(LED_BUILTIN, OUTPUT);
  pedal.setMode(ButtonMode::PullDown);
  pedal.setDebounceDeadtime(100);
  pedal.addPressTask(ftest);
  //pedal.addPressTask(pedal_callback);
  pedal.addReleaseTask(pedal_release_callback);

  Serial.begin(9600);

/*

      motor.setDirection(StepDirection::Left);
  motor.setRPM(200);
  motor.setSteps(1600);
  motor.stop();
*/
  //nextion_callback_setup();
  //nexInit();
  //mwc.init();
  //mwc.set(0, 200, 1600);


}

void loop()
{

  AVR_Button::updateButtons(millis());
  //mwc.run();
  doser.run(micros());
  //motor.run(micros());
  if(state::operation != nullptr)
  {
    state::operation();
  }

  //nexLoop(nex_listen_list);

}


