#include <unity.h>
#include <AVR_Button.h>
#include <CircularBuffer.h>
#include <EEPROMController.h>
#include <AVR_StepMotor.h>

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


void test_eeprom_write_read()
{

    uint8_t* address = (uint8_t*)2;
    EEPROMController eeprom(512);
    char mydata[] = "hello";
    char* received = new char[sizeof(mydata)];
    eeprom.write((uint8_t*)mydata, address, sizeof(mydata));
    eeprom.read((uint8_t*)received, address, sizeof(mydata));

    TEST_ASSERT_EQUAL_CHAR_ARRAY(received, mydata, sizeof(mydata));
}



void test_eeprom_save_get_config()
{
    EEPROMController eep(1024);
    DosingConfiguration cfg = DosingConfiguration();
    cfg.id = 5;
    cfg.motor_rpm = 400;
    cfg.motor_steps = 1600;
    cfg.steps_to_run = 12000;
    eep.save_configuration(cfg);
    DosingConfiguration cfg_received = DosingConfiguration();
    eep.get_configuration(&cfg_received, cfg.id);
    TEST_ASSERT_EQUAL(cfg.id, cfg_received.id);
    TEST_ASSERT_EQUAL(cfg.motor_rpm, cfg_received.motor_rpm);
    TEST_ASSERT_EQUAL(cfg.motor_steps, cfg_received.motor_steps);
    TEST_ASSERT_EQUAL(cfg.steps_to_run, cfg_received.steps_to_run);
}


void test_eeprom_restore_config()
{
    EEPROMController eep(1024);
    DosingConfiguration cfg = DosingConfiguration();
    cfg.id = 5;
    cfg.motor_rpm = 400;
    cfg.motor_steps = 1600;
    cfg.steps_to_run = 12000;
    eep.save_configuration(cfg);
    uint8_t t = 0;

    // corrupt the data stored in eeprom
    eep.write(&t, reinterpret_cast<uint8_t*>(eeprom::get_save_address<DosingConfiguration>(cfg.id)), 1);
    DosingConfiguration cfg_received = DosingConfiguration();
    eep.get_configuration(&cfg_received, cfg.id);

    // received configuration must be empty
    TEST_ASSERT_EQUAL(cfg.id, cfg_received.id);
    TEST_ASSERT_EQUAL(0, cfg_received.motor_rpm);
    TEST_ASSERT_EQUAL(0, cfg_received.motor_steps);
    TEST_ASSERT_EQUAL(0, cfg_received.steps_to_run);

}

void test_dosing_controller_manual()
{
    AVR_StepMotor motor = AVR_StepMotor(0,0,0);
    DosingController controller = DosingController(&motor);
    DosingConfiguration cfg;
    cfg.id = 1;
    cfg.motor_rpm = 100;
    cfg.motor_steps = 1800;
    cfg.steps_to_run = 2000;
    controller.configure(cfg);
    TEST_ASSERT_EQUAL(controller.isDosing(), false);
    controller.setMode(DosingMode::Manual);
    controller.run(10);
    TEST_ASSERT_EQUAL(controller.isDosing(), false);
    controller.dose();
    TEST_ASSERT_EQUAL(controller.isDosing(), true);
    controller.run(30000);
    TEST_ASSERT_EQUAL(controller.isDosing(), true);
    controller.stop();
    TEST_ASSERT_EQUAL(controller.isDosing(), false);

}

void test_dosing_controller_auto()
{
    AVR_StepMotor motor = AVR_StepMotor(0,0,0);
    DosingController controller = DosingController(&motor);
    DosingConfiguration cfg;
    cfg.id = 1;
    cfg.motor_rpm = 100;
    cfg.motor_steps = 1600;
    cfg.steps_to_run = 5;
    controller.configure(cfg);
    controller.setMode(DosingMode::Auto);
    TEST_ASSERT_EQUAL(controller.isDosing(), false);
    controller.dose();
    controller.run(30);
    TEST_ASSERT_EQUAL(controller.isDosing(), true);
    for(int i = 0 ; i< 200; i++)
    {
        controller.run(i*1000);
    }
    TEST_ASSERT_EQUAL(controller.isDosing(), false);
    
    
}


void test_doser_auto()
{
    auto motor = AVR_StepMotor(0,0,0);
    DosingController doser1(&motor);
    DosingConfiguration cfg = DosingConfiguration();
    cfg.motor_rpm = 200;
    cfg.motor_steps = 1600;
    cfg.steps_to_run = 3200;

    doser1.configure(cfg);
    doser1.setMode(DosingMode::Auto);
    TEST_ASSERT_EQUAL(doser1.isDosing(), false);

    doser1.dose();
    TEST_ASSERT_EQUAL(doser1.isDosing(), true);
    for(int i = 0; i<9000;i++) {
        doser1.run(i);    
    }
    TEST_ASSERT_EQUAL(false, doser1.isDosing());

    doser1.dose();
    TEST_ASSERT_EQUAL(true, doser1.isDosing());
    for(int i = 9000; i< 9050; i++) 
    {
      doser1.run(i);
    }

    TEST_ASSERT_EQUAL(true, doser1.isDosing());
    for(int i = 9050; i< 15000; i++)
    {
        doser1.run(i);
    }

    TEST_ASSERT_EQUAL(false, doser1.isDosing());

}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_circular_buffer);
    RUN_TEST(test_eeprom_save_get_config);
    RUN_TEST(test_eeprom_write_read);
    RUN_TEST(test_dosing_controller_manual);
    RUN_TEST(test_dosing_controller_auto);
    RUN_TEST(test_eeprom_restore_config);  // CALL AFTER OTHER EEPROM TESTS
    RUN_TEST(test_doser_auto);

    return UNITY_END();
}
