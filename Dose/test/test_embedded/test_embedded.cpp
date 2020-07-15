#include <unity.h>
#include <AVR_Button.h>
#include <CircularBuffer.h>
#include <EEPROMController.h>

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



void test_eeprom_save_restore_config()
{
    EEPROMController eep(1024);
    DosingConfiguration cfg = DosingConfiguration();
    cfg.id = 5;
    cfg.motor_rpm = 400;
    cfg.motor_steps = 1600;
    cfg.steps_to_run = 12000;
    eep.save_configuration(cfg);
    DosingConfiguration cfg_received = DosingConfiguration();
    eep.get_configuration(&cfg_received, 5);
    TEST_ASSERT_EQUAL(cfg.id, cfg_received.id);
    TEST_ASSERT_EQUAL(cfg.motor_rpm, cfg_received.motor_rpm);
    TEST_ASSERT_EQUAL(cfg.motor_steps, cfg_received.motor_steps);
    TEST_ASSERT_EQUAL(cfg.steps_to_run, cfg_received.steps_to_run);


}

/*
void test_eeprom_write_read_block()
{
    auto address = reinterpret_cast<uint8_t*>(100);
    EEPROMController eep(1024);
    char mydata[] = "hello";
    char* received = new char[sizeof(mydata)];
    eep.write_block(&mydata, address, sizeof(mydata));

}

*/

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_circular_buffer);
    RUN_TEST(test_eeprom_save_restore_config);
    RUN_TEST(test_eeprom_write_read);

    return UNITY_END();
}
