#ifdef ARDUINO                  
#include <Arduino.h>
#include <AVR_StepMotor.h>
#include <AVR_Button.h>
#include <DosingController.h>
#include <EEPROMController.h>
#include <SoftwareSerial.h>
typedef AVR_StepMotor StepMotorBase;
#endif

#include <globals.h>
#include <program.h>
#include <Nextion.h>
#include <Terminal.h>

//EEPROMController eeprom = EEPROMController(1024);
ButtonFunc pedal_callback;
ButtonFunc pedal_release_callback;
Term::Terminal terminal{debug_serial};
//Term::Terminal terminal{Serial};
uint32_t last_ticks = 0;
uint32_t terminal_update_cycle = 500;
void print_system();


void setup()
{
  pedal_callback = pedal_default_fill_callback;
  pedal_release_callback = pedal_default_fill_release_callback;
  //pedal_release_callback = pedal_default_fill_release_callback;
  doser = DosingController(&motor);
  auto test_cfg = DosingConfiguration();
  test_cfg.motor_rpm = 400;
  test_cfg.motor_steps = 1600;
  test_cfg.steps_to_run = 1600;
  current_cfg = test_cfg;
  doser.configure(current_cfg);
  doser.setMode(DosingMode::Manual);

  pinMode(LED_BUILTIN, OUTPUT);
  pedal.setMode(ButtonMode::PullDown);
  pedal.setDebounceDeadtime(100);
  pedal.addPressTask(pedal_callback);
  pedal.addReleaseTask(pedal_release_callback);
  //Serial.begin(9600);
  debug_serial.begin(9600);
  nSerial.begin(9600);

/*

      motor.setDirection(StepDirection::Left);
  motor.setRPM(200);
  motor.setSteps(1600);
  motor.stop();
*/

  nextion_callback_setup();
  nexInit();
  terminal.hideCursor(true);
  read_callibrations();
  state::remaining_to_fill = 10;
  state::delay_between_fills = 2000;


}

void loop()
{

  AVR_Button::updateButtons(millis());
  doser.run(micros());
  //motor.run(micros());

  nexLoop(nex_listen_list);
  if(state::operation != nullptr)
  {
    state::operation();
  }
  if(millis()  - last_ticks > terminal_update_cycle)
  {
    last_ticks = millis();
    print_system();
  }
  
}


void print_system()
{
  
  static char buf[24];
  terminal.clear();
  terminal.resetCursor();
  terminal.setTextColor(Term::Color::Yellow);
  terminal.bold(true);
  terminal.moveCursor(Term::Direction::Left, 20);
  debug_serial.println(F("DOSE8 DEBUG MODE"));
  terminal.setTextColor(Term::Color::Blue);
  debug_serial.println(F("MOTOR"));
  terminal.bold(false);
  terminal.setTextColor(Term::Color::White);
  debug_serial.print(F("running = "));
  motor.isActive() ? terminal.setTextColor(Term::Color::Green) : terminal.setTextColor(Term::Color::Red);
  motor.isActive() ? debug_serial.println("true") : debug_serial.println("false");
  terminal.setTextColor(Term::Color::White);
  snprintf(buf, 24, ("steps = %8ld"), motor.getTotalSteps());
  debug_serial.println(buf);
  snprintf(buf, 24, ("rpm = %3d"), motor.getRPM());
  debug_serial.println(buf);
  

  debug_serial.println(" ");
  terminal.setTextColor(Term::Color::Blue);
  terminal.bold(true);
  debug_serial.println(F("PEDAL"));
  terminal.bold(false);
  terminal.setTextColor(Term::Color::White);
  debug_serial.print(F("state = "));
  pedal.checkState() == ButtonState::Pressed ? debug_serial.println(F("pressed")) : debug_serial.println(F("released"));
  debug_serial.println(" ");

  terminal.setTextColor(Term::Color::Blue);
  terminal.bold(true);
  debug_serial.println(F("CURRENT_CONFIG"));
  terminal.bold(false);
  terminal.setTextColor(Term::Color::White);
  snprintf(buf, 24, ("id = %d"), current_cfg.id);
  debug_serial.println(buf);
  snprintf(buf, 24, ("rpm = %3d"), current_cfg.motor_rpm);
  debug_serial.println(buf);
  snprintf(buf, 24, ("steps_to_run = %5d"), current_cfg.steps_to_run);
  debug_serial.println(buf);
  snprintf(buf, 24, ("radius = %3d"), current_cfg.pipe_radius);
  debug_serial.println(buf);
  snprintf(buf, 24, ("volume = %4d"), current_cfg.volume);
  debug_serial.println(buf);

  debug_serial.println(" ");

  terminal.setTextColor(Term::Color::Blue);
  terminal.bold(true);
  debug_serial.println(F("PROGRAM"));
  terminal.bold(false);
  terminal.setTextColor(Term::Color::White);
  debug_serial.print(("mode = "));
  if(state::mode == ProgramMode::Manual)
    debug_serial.println(F("Manual"));
  else if(state::mode == ProgramMode::Auto)
    debug_serial.println(F("Auto"));
  else if(state::mode == ProgramMode::Callibration)
    debug_serial.println(F("Callibration"));
  snprintf(buf, 24, ("remaining = %3d"), state::remaining_to_fill);
  debug_serial.println(buf);

  snprintf(buf, 24, ("wait_time = %4d"), state::delay_between_fills);
  debug_serial.println(buf);

  debug_serial.println(" ");

  terminal.setTextColor(Term::Color::Cyan);
  terminal.bold(true);
  if(state::mode == ProgramMode::Callibration) terminal.blink(true);
  debug_serial.println(F("CALLIBRATION"));
  terminal.bold(false);
  terminal.blink(false);
  terminal.setTextColor(Term::Color::White);
  snprintf(buf, 24, ("callib_steps = %5ld"), state::callibration_steps);
  debug_serial.println(buf);

  debug_serial.println(" ");
  debug_serial.print(F("AAA"));

}
