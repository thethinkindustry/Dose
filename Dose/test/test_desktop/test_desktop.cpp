#include <unity.h>
#include <StaticTimer.h>
#include <Button.h>
#include <EEPROMMock.h>
#include <StepMotorMock.h>
#include <DosingController.h>
#include <CircularBuffer.h>


int testvar = 0;



void timerfunc(void*)
{
    testvar++;
}

void test_function_statictimer_update()
{
    StaticTimer timer(200);
    timer.addTask(timerfunc);
    TEST_ASSERT_EQUAL(0, testvar);
    timer.update(100);
    TEST_ASSERT_EQUAL(0, testvar);
    timer.update(200);
    TEST_ASSERT_EQUAL(0, testvar);
    timer.update(220);
    TEST_ASSERT_EQUAL(1, testvar);
    timer.update(500);
    TEST_ASSERT_EQUAL(2, testvar);

}


void test_button_pullup()
{
    int time = 0;
    Button b1 = Button();
    b1.setDebounceDeadtime(5);
    b1.setMode(ButtonMode::PullUp);
    b1.update(0, 30);
    TEST_ASSERT_EQUAL(ButtonState::Pressed ,b1.checkState());
    b1.update(0,60);
    TEST_ASSERT_EQUAL(ButtonState::Pressed ,b1.checkState());
    b1.update(1, 90);
    TEST_ASSERT_EQUAL(ButtonState::Released ,b1.checkState());
    b1.update(1,120);
    TEST_ASSERT_EQUAL(ButtonState::Released ,b1.checkState());
    b1.update(0,150);
    TEST_ASSERT_EQUAL(ButtonState::Pressed ,b1.checkState());

}

void test_button_pulldown()
{
    Button b1 = Button();
    b1.setMode(ButtonMode::PullDown);
    b1.setDebounceDeadtime(5);
    b1.update(1, 30);
    TEST_ASSERT_EQUAL(ButtonState::Pressed ,b1.checkState());
    b1.update(1,60);
    TEST_ASSERT_EQUAL(ButtonState::Pressed ,b1.checkState());
    b1.update(0, 90);
    TEST_ASSERT_EQUAL(ButtonState::Released ,b1.checkState());
    b1.update(0,120);
    TEST_ASSERT_EQUAL(ButtonState::Released ,b1.checkState());
    b1.update(1,150);
    TEST_ASSERT_EQUAL(ButtonState::Pressed ,b1.checkState());
}

void test_eeprom_write_read()
{

    uint8_t* address = (uint8_t*)2;
    EEPROMMock eeprom(512);
    char mydata[] = "hello";
    char* received = new char[sizeof(mydata)];
    eeprom.write((uint8_t*)mydata, address, sizeof(mydata));
    eeprom.read((uint8_t*)received, address, sizeof(mydata));

    TEST_ASSERT_EQUAL_CHAR_ARRAY(received, mydata, sizeof(mydata));
}

void test_eeprom_save_restore_config()
{
    EEPROMMock eep(1024);
    DosingConfiguration cfg = DosingConfiguration();
    cfg.id = 1;
    cfg.motor_rpm = 400;
    cfg.motor_steps = 1600;
    cfg.steps_to_run = 12000;
    eep.save_configuration(cfg);

    DosingConfiguration cfg_received = DosingConfiguration();
    eep.get_configuration(&cfg_received, 1);

    TEST_ASSERT_EQUAL(cfg.id, cfg_received.id);
    TEST_ASSERT_EQUAL(cfg.motor_rpm, cfg_received.motor_rpm);
    TEST_ASSERT_EQUAL(cfg.motor_steps, cfg_received.motor_steps);
    TEST_ASSERT_EQUAL(cfg.steps_to_run, cfg_received.steps_to_run);


}


void test_button_debounce()
{
    TEST_IGNORE();
    Button b = Button();
    b.setMode(ButtonMode::PullDown);
    b.setDebounceDeadtime(5);
    b.update(1, 30);
    TEST_ASSERT_EQUAL(ButtonState::Pressed, b.checkState());
    b.update(0,40);
    TEST_ASSERT_EQUAL(ButtonState::Pressed, b.checkState());
    b.update(1,40);
    TEST_ASSERT_EQUAL(ButtonState::Pressed, b.checkState());
    b.update(0, 81);
    TEST_ASSERT_EQUAL(ButtonState::Released, b.checkState());


}

void test_button_debounce2()
{
    Button b = Button();
    b.setMode(ButtonMode::PullDown);
    b.setDebounceDeadtime(50);
    b.update(1, 60);
    TEST_ASSERT_EQUAL(ButtonState::Pressed, b.checkState());
    b.update(0,70);
    TEST_ASSERT_EQUAL(ButtonState::Pressed, b.checkState());
    b.update(1,80);
    TEST_ASSERT_EQUAL(ButtonState::Pressed, b.checkState());
    b.update(0, 111);
    TEST_ASSERT_EQUAL(ButtonState::Released, b.checkState());

}

void test_circular_buffer()
{
    CircularBuffer<uint8_t> buf(30);
    
    TEST_ASSERT_EQUAL(buf.capacity(), 30);
    TEST_ASSERT_EQUAL(buf.isEmpty(), true);
    TEST_ASSERT_EQUAL(buf.isFull(), false);
    buf.put(1);
    TEST_ASSERT_EQUAL(buf.isEmpty(), false);
    auto val = buf.get();
    TEST_ASSERT_EQUAL(val, 1);
    TEST_ASSERT_EQUAL(buf.isEmpty(), true);
    for(int i = 0; i< 60; i++) buf.put(i);
    TEST_ASSERT_EQUAL(buf.isFull(), true);
    
}

void test_dosing_controller()
{
    StepMotorMock motor = StepMotorMock();
    DosingConfiguration cfg;
    DosingController doser(&motor);
    doser.configure(cfg);
    doser.dose();
    TEST_ASSERT_EQUAL(true, doser.isDosing());
    

}



int main()
{

    UNITY_BEGIN();
    RUN_TEST(test_function_statictimer_update);
    RUN_TEST(test_button_pullup);
    RUN_TEST(test_button_pulldown);
    RUN_TEST(test_button_debounce);
    RUN_TEST(test_button_debounce2);
    RUN_TEST(test_eeprom_write_read);
    RUN_TEST(test_eeprom_save_restore_config);
    RUN_TEST(test_dosing_controller);
    RUN_TEST(test_circular_buffer);
    return UNITY_END();
}
