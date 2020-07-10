#ifndef _Button_
#define _Button_
#include <stdint.h>
#define BUTTON_MAX_BUTTONS 5
#define BUTTON_MAX_TASKS 5

using ButtonFunc = void (*) (void*);

enum ButtonMode
{
    PullUp,
    PullDown
};

enum ButtonState
{
    Pressed,
    Released
};


class Button
{

    private:
    static const int maxTasks = BUTTON_MAX_TASKS;
    static const int max_buttons = BUTTON_MAX_BUTTONS;
    int index_pressTask = 0;
    int index_releaseTask = 0;
    int button_index = 0;



    protected:
    ButtonMode mode = ButtonMode::PullUp;
    ButtonState state = ButtonState::Released;
    ButtonFunc pressTasks[maxTasks];
    ButtonFunc releaseTasks[maxTasks];

    public:
    Button();
    void addPressTask(ButtonFunc func);
    void addReleaseTask(ButtonFunc func);
 
    ButtonState checkState();

    void update(uint8_t logic);


};

#endif