#include <unity.h>
#include <StaticTimer.h>
#include <Button.h>
#include <EEPROMMock.h>

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
    timer.update(220);
    //TEST_ASSERT_EQUAL(1, testvar);
    timer.update(500);
    //TEST_ASSERT_EQUAL(2, testvar);

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


int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_function_statictimer_update);
    RUN_TEST(test_button_pullup);
    RUN_TEST(test_button_pulldown);
    RUN_TEST(test_button_debounce);
    RUN_TEST(test_button_debounce2);
    RUN_TEST(test_eeprom_write_read);
    return UNITY_END();
}
