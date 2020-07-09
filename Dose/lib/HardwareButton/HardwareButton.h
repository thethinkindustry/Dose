
#include <Button.h>

class HardwareButton: public Button
{
    public:
    HardwareButton();
    HardwareButton(int ps);
    void update();
};