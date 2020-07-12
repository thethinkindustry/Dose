#ifndef _EEPROMController_
#define _EEPROMController_

#include <PersistentStorage.h>

#include <avr/eeprom.h>

class EEPROMController : public PersistentStorage
{
    private:
    EEPROMController();

    public:
    EEPROMController(uint32_t size);
    void write(uint8_t* data, uint8_t* address, int nbytes);
    void read(uint8_t* destination, uint8_t* address, int nbytes);
};
#endif