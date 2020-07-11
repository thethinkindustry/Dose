#ifndef _EEPROMMock_
#define _EEPROMMock_
#include <PersistentStorage.h>

class EEPROMMock : public PersistentStorage
{
    private:
    EEPROMMock();
    uint8_t* memory;

    public:
    EEPROMMock(uint32_t size);
    void write(uint8_t* data, uint8_t* address, int nbytes);
    void read(uint8_t* destination, uint8_t* address, int nbytes);
};

#endif