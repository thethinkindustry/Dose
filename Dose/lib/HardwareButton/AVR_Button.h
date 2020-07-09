
#include <Button.h>

class AVR_Button: public Button
{

    private:
    int pin;
    int port;


    public:
    AVR_Button();
    AVR_Button(int pin, int port);
    void update(int logic);

};