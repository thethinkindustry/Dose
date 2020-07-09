#include <HardwareButton.h>

HardwareButton::HardwareButton()
{

}

HardwareButton::HardwareButton(int ps)
{  
    pool_size = ps;
    pressTasks = new ButtonFunc*[5];
    releaseTasks = new ButtonFunc*[5];
}

void HardwareButton::update()
{
    
}