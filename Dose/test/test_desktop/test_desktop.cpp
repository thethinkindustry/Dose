#include <unity.h>
#include <StaticTimer.h>

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

}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_function_statictimer_update);
    return UNITY_END();
}
