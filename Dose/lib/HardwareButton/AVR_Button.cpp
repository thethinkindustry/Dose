#include <AVR_Button.h>


int AVR_Button::total_buttons = 0;
AVR_Button* AVR_Button::buttons[BUTTON_MAX_BUTTONS];

// ARDUINO SPECIFIC
#ifdef ARDUINO
#include <Arduino.h>
AVR_Button::AVR_Button(int pin)
{
    add(this);
    uno_pin = pin;
    pinMode(pin, INPUT);
}
#endif
AVR_Button::AVR_Button()
{
    add(this);

    
}

AVR_Button::AVR_Button(int _port, int _pin)
:port{_port}, pin{_pin}
{  
    add(this);
}


void AVR_Button::add(AVR_Button* b)
{
    buttons[total_buttons] = b;
    total_buttons++;
}

int AVR_Button::total()
{
    return total_buttons;
}

AVR_Button** AVR_Button::getButtons()
{
    return buttons;
    
}



