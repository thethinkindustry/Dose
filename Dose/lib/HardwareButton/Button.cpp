
#include <Button.h>



ButtonFunc::ButtonFunc()
{

}

ButtonFunc::ButtonFunc(void* (f) (void*))
{
    func = f;
}

void* ButtonFunc::operator()(void* data)
{
    func(data);
}


void Button::addPressTask(ButtonFunc* f)
{
    pressTasks[index] = f;
    index++;
}

void Button::addReleaseTask(ButtonFunc* f)
{

} 

void Button::removePressTask(ButtonFunc* f)
{

}

void Button::removeReleaseTask(ButtonFunc* f)
{

}

ButtonState Button::checkState()
{
    return state;
}

