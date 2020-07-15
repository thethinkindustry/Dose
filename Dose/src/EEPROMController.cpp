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

void EEPROMController::write_block(const void* src, void* dst, size_t n)
{
    eeprom_busy_wait();
    eeprom_write_block(src, dst, n);
}

void EEPROMController::read_block(void* dst, const void* src, size_t n)
{
    eeprom_busy_wait();
    eeprom_read_block(dst, src, n);
}

void EEPROMController::save_configuration(DosingConfiguration cfg)
{
    auto write_address = reinterpret_cast<uint8_t*>(eeprom::first_save_address + sizeof(DosingConfiguration)*cfg.id);
    write((uint8_t*)&cfg, write_address, sizeof(DosingConfiguration));
}

void EEPROMController::get_configuration(DosingConfiguration* cfg, uint8_t id)
{
    auto read_address = reinterpret_cast<uint8_t*>(eeprom::first_save_address + sizeof(DosingConfiguration)*id);
    read( (uint8_t*)cfg, read_address, sizeof(DosingConfiguration));
    
}