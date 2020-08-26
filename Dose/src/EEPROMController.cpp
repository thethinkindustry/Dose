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
    cfg.checksum = calculateChecksum(&cfg);
    auto write_address = (uint8_t*)(40*cfg.id);
    //auto write_address = reinterpret_cast<uint8_t*>(eeprom::get_save_address<DosingConfiguration>(cfg.id));    
    //auto write_address = reinterpret_cast<uint8_t*>(eeprom::first_save_address + sizeof(DosingConfiguration)*cfg.id);
    write((uint8_t*)&cfg, write_address, sizeof(DosingConfiguration));
}

void EEPROMController::get_configuration(DosingConfiguration* cfg, uint8_t id)
{
    auto read_address = (uint8_t*)(40*id);
    //auto read_address = reinterpret_cast<uint8_t*>(eeprom::get_save_address<DosingConfiguration>(id));
    read( (uint8_t*)cfg, read_address, sizeof(DosingConfiguration));
    // if the configuration is corrupted replace it with an empty one
    
    if(!checkIntegrity(cfg))
    {
        restoreConfig(id);
        *cfg = DosingConfiguration();
        cfg->id = id;
    }
    
    cfg->id = id;
}

void EEPROMController::restoreConfig(uint8_t id)
{
    auto config = DosingConfiguration();
    config.id = id;
    save_configuration(config);
}

uint8_t EEPROMController::calculateChecksum(DosingConfiguration* cfg)
{
    auto ptr = reinterpret_cast<uint8_t*>(cfg);
    uint32_t sum = 0;
    for(int i = 0; i<sizeof(DosingConfiguration) - 1; i++)
    {
        sum += *ptr;
        ++ptr;
    }
    
    return (0xFF - static_cast<uint8_t>(sum));
}

bool EEPROMController::checkIntegrity(DosingConfiguration* cfg)
{
    auto chksum = cfg->checksum;
    auto sum = calculateChecksum(cfg);
    return sum == chksum ? true : false;
}