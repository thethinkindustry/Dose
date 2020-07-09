#include <AVR_Button.h>

AVR_Button::AVR_Button()
{

    pressTasks = new ButtonFunc*[5];
    releaseTasks = new ButtonFunc*[5];
    
}

AVR_Button::AVR_Button(int _port, int _pin)
{  

    port = _port;
    pin = _pin;
    pressTasks = new ButtonFunc*[5];
    releaseTasks = new ButtonFunc*[5];

}

void AVR_Button::update(int logic)
{
    if(mode == ButtonMode::PullDown)
    {
        if(logic == 1 && state == ButtonState::Released)
        {
            for(int i = 0; i< pool_size; i++) {
                if(pressTasks[i] != nullptr)
                    (*pressTasks[i])(nullptr);
                    
            }
            state = ButtonState::Pressed;
        }

        else
        {
            for(int i = 0; i< pool_size; i++) {
                if(releaseTasks[i] != nullptr)
                    (*releaseTasks[i])(nullptr);
            }
            state = ButtonState::Released;
        }
        
    }

    else
    {
        if(logic == 0 && state == ButtonState::Released)
        {
            for(int i = 0; i< pool_size; i++) {
                if(pressTasks[i] != nullptr)
                    (*pressTasks[i])(nullptr);
                    
            }
            state = ButtonState::Pressed;
        }

        else
        {
            for(int i = 0; i< pool_size; i++) {
                if(releaseTasks[i] != nullptr)
                    (*releaseTasks[i])(nullptr);
            }
            state = ButtonState::Released;
        }
    }

 
}


