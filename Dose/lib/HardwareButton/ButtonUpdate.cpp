#include <ButtonUpdater.h>

ButtonUpdater::ButtonUpdater(int m_buttons)
{
    max_buttons = m_buttons;
    buttons = new Button*[max_buttons];
    for(int i = 0; i<max_buttons; i++)
        buttons[i] = nullptr;
}

void ButtonUpdater::update()
{
    for(int i = 0; i < max_buttons; i++)
    {
        if(buttons[i] != nullptr)
        {
            
            //TODO - check pins
        }
    }
}