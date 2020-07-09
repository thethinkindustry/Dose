#include <unity.h>
#include <StepMotorMocks.h>
//#include <StepMotor.h>

StepMotor* motor = nullptr;



void test_function_stepmotor_initilization()
{
    motor = new StepMotorMock(0, 0, 0);
    TEST_ASSERT_EQUAL(0, motor->getRPM());
    TEST_ASSERT_EQUAL(StepDirection::Left, motor->getDirection());
    TEST_ASSERT_EQUAL(false, motor->isActive());
}

void test_function_stepmotor_run()
{
    motor = new StepMotorMock(0, 0, 0);
    motor->run();
    TEST_ASSERT_EQUAL(true, motor->isActive());
}

int main()
{
    
    UNITY_BEGIN();
    RUN_TEST(test_function_stepmotor_initilization);
    return UNITY_END();
}