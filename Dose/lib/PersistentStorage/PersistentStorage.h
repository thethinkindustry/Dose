#ifndef _PersistentStorage_
#define _PersistentStorage_

#include <stdint.h>

class PersistentStorage
{
    protected:
    uint32_t size;
    uint8_t granularity = sizeof(uint8_t);


    public:

    virtual void write(uint8_t* data, uint8_t* address, int nbytes) = 0;
    virtual void read(uint8_t* destination, uint8_t* address, int nbytes) = 0;
    
};

#endif