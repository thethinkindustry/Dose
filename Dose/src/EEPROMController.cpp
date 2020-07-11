#include <EEPROMController.h>
#include <stdint.h>

EEPROMController::EEPROMController(uint32_t size)
{
    this->size = size;
}

void EEPROMController::write(uint8_t* data, uint8_t* address, int nbytes)
{
    eeprom_busy_wait();
    eeprom_write_block(data, address, nbytes);
}

void EEPROMController::read(uint8_t* destination, uint8_t* address, int nbytes)
{
    eeprom_busy_wait();
    eeprom_read_block(destination, address, nbytes);
}
