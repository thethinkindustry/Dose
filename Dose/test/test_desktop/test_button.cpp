#include <unity.h>
#include <AVR_Button.h>

class TestAVR_Button : public AVR_Button
{
    public:
    TestAVR_Button():AVR_Button()
    {

    }
    void simulatePress()
    {
        this->state = ButtonState::Pressed;
        this->update();
    }
};

void* func (void*)
{
    return nullptr;
}


void test_function_button_init()
{
    TestAVR_Button* button = new TestAVR_Button();
    ButtonFunc f(func);
    button->addPressTask(&f);
    button->update();

    AVR_Button.iterateLoop();
}

int main()
{
    
    UNITY_BEGIN();
    RUN_TEST(test_function_button_init);
    return UNITY_END();
}