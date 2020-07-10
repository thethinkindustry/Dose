#include <Button.h>



//TODO- add max control
Button::Button()
{

}

//TODO- add bound control
void Button::addPressTask(ButtonFunc f)
{
    pressTasks[index_pressTask] = f;
    index_pressTask++;
}

//TODO- add bound control
void Button::addReleaseTask(ButtonFunc f)
{
    releaseTasks[index_releaseTask] = f;
    index_releaseTask++;
} 

ButtonState Button::checkState()
{
    return state;
}



void Button::update(uint8_t logic)
{
    if(mode == ButtonMode::PullDown)
    {
        if(logic == 1 && state == ButtonState::Released)
        {
            for(int i = 0; i< index_releaseTask; i++) {
                if(pressTasks[i] != nullptr)
                    (*pressTasks[i])(nullptr);
                    
            }
            state = ButtonState::Pressed;
        }

        else
        {
            for(int i = 0; i< index_pressTask; i++) {
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
            for(int i = 0; i< index_pressTask; i++) {
                if(pressTasks[i] != nullptr)
                    (*pressTasks[i])(nullptr);
                    
            }
            state = ButtonState::Pressed;
        }

        else
        {
            for(int i = 0; i< index_releaseTask; i++) {
                if(releaseTasks[i] != nullptr)
                    (*releaseTasks[i])(nullptr);
            }
            state = ButtonState::Released;
        }
    }

 
}

