#include <EEPROMMock.h>

EEPROMMock::EEPROMMock(uint32_t size)
{
    this->size = size;
    memory = new uint8_t[size];
}

void EEPROMMock::write(uint8_t* data, uint8_t* address, int nbytes)
{
    auto base_address = reinterpret_cast<uint64_t>(memory) + reinterpret_cast<uint64_t>(address);
    auto target = reinterpret_cast<uint8_t*>(base_address);
    uint8_t* ptr = data;
    for(int i = 0; i< nbytes; i++)
    {
        
        *target = *ptr;
        ptr++;
        address++;
        target++;
    
    }
}

void EEPROMMock::read(uint8_t* destination, uint8_t* address, int nbytes)
{
    auto base_address = reinterpret_cast<uint64_t>(memory) + reinterpret_cast<uint64_t>(address);
    auto from = reinterpret_cast<uint8_t*>(base_address);
    uint8_t* ptr = destination;
    for(int i = 0; i< nbytes; i++)
    {
        *ptr = *from;
        ptr++;
        address++;
        from++;
    
    }
}

void EEPROMMock::write_block(const void* src, void* dst, size_t n){
    auto from = (uint8_t*)src;
    auto to = (uint8_t*)dst;
    for(n; n > 0; n--)
    {
        write(from, to, 1);
        to++;
        from++;
    }
}

void EEPROMMock::read_block(void* dst, const void* src, size_t n)
{
    auto from = (uint8_t*)src;
    auto to = (uint8_t*)dst;
    for(n; n > 0; n--)
    {
        read(to, from, 1);
        to++;
        from++;
    }
}

void EEPROMMock::save_configuration(DosingConfiguration cfg)
{
    auto write_address = reinterpret_cast<uint8_t*>(eeprom::first_save_address + sizeof(DosingConfiguration)*cfg.id);
    write((uint8_t*)&cfg, write_address, sizeof(DosingConfiguration));
}

void EEPROMMock::get_configuration(DosingConfiguration* cfg, uint8_t id)
{
    auto read_address = reinterpret_cast<uint8_t*>(eeprom::first_save_address + sizeof(DosingConfiguration)*id);
    read((uint8_t*)cfg, read_address, sizeof(DosingConfiguration));
}