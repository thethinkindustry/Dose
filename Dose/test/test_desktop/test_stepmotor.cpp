#include <unity.h>
#include <AVR_StepMotor.h>


void test_function_stepmotor_initilization()
{
    StepMotor* motor = new AVR_StepMotor(0, 0, 0);
    TEST_ASSERT_EQUAL(0, motor->getRPM());
    TEST_ASSERT_EQUAL(StepDirection::Left, motor->getDirection());
    TEST_ASSERT_EQUAL(false, motor->isActive());
}



int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_function_stepmotor_initilization);
    return UNITY_END();
}