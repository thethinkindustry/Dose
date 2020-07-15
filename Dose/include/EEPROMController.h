#ifndef _EEPROMController_
#define _EEPROMController_

#include <PersistentStorage.h>
#include <avr/eeprom.h>
#include <DosingController.h>


//TODO- add data integrity control and error check 

namespace eeprom
{
    constexpr uint16_t first_save_address = 4;

    constexpr uint32_t max_configs = 10;

}


class EEPROMController : public PersistentStorage
{
    private:
    EEPROMController();

    public:
    EEPROMController(uint32_t size);
    void write(uint8_t* data, uint8_t* address, int nbytes);
    void read(uint8_t* destination, uint8_t* address, int nbytes);
    void write_block(const void* src, void* dst, size_t n);
    void read_block(void* dst, const void* src, size_t n);
    void save_configuration(DosingConfiguration cfg);
    void get_configuration(DosingConfiguration* cfg, uint8_t id);
};
#endif