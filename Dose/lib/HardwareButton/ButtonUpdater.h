#include <AVR_Button.h>

class ButtonUpdater
{
    private:
    int max_buttons = 5;
    Button** buttons;
    public:
    ButtonUpdater();
    ButtonUpdater(int m_buttons);
    void update();
};