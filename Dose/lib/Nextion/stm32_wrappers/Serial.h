#ifndef _STM32_SERIAL_
#define _STM32_SERIAL_

using SerialStruct = void*;
class Serial
{
    
    private:
    SerialStruct hwserial;
    int timeout_ms;
    Serial();
    public:
    Serial(SerialStruct);
    void begin(int baudrate);
    void setTimeout(int t);
    void print();
    void write();
    //TODO- use correct type and template
    int read();
    int end();
    bool available();
};



#endif