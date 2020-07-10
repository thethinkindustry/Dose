#include <unity.h>
#include <StaticTimer.h>
#include <Button.h>

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
    TEST_ASSERT_EQUAL(1, testvar);
    timer.update(500);
    TEST_ASSERT_EQUAL(2, testvar);

}


void test_button_pullup()
{
    int time = 0;
    Button b1 = Button();
    ButtonState old_state = b1.checkState();
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
int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_function_statictimer_update);
    RUN_TEST(test_button_pullup);
    RUN_TEST(test_button_pulldown);
    return UNITY_END();
}
