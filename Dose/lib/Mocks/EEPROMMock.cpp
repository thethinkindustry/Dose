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