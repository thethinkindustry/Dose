#include <unity.h>
#include <AVR_Button.h>
#include <CircularBuffer.h>

void test_button_pullup()
{
    TEST_ASSERT_EQUAL(1,1);
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




int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_button_pullup);
    RUN_TEST(test_circular_buffer);
    return UNITY_END();
}
