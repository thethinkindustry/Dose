#ifndef _AVR_Button_
#define _AVR_Button_

#include <Button.h>
#include <Arduino.h>
class AVR_Button: public Button
{

    private:
    int pin;
    int port;
    static AVR_Button* buttons[];
    static int total_buttons;
    static void add(AVR_Button* b);

    public:
    AVR_Button();
#ifdef ARDUINO
    int uno_pin;
    AVR_Button(int pin);
#endif
    AVR_Button(int pin, int port);
    static int total();
    static AVR_Button** getButtons();
    static void updateButtons(uint64_t ticks); 

};

#endif