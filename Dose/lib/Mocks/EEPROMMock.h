#ifndef _EEPROMMock_
#define _EEPROMMock_
#include <PersistentStorage.h>
#include <stdint.h>
#include <DosingController.h>
namespace
{
    using size_t = __SIZE_TYPE__;
}


namespace eeprom
{
    constexpr uint16_t first_save_address = 4;

    constexpr uint32_t max_configs = 10;

}





class EEPROMMock : public PersistentStorage
{
    private:
    EEPROMMock();
    uint8_t* memory;

    public:
    EEPROMMock(uint32_t size);
    void write(uint8_t* data, uint8_t* address, int nbytes);
    void read(uint8_t* destination, uint8_t* address, int nbytes);
    void write_block(const void* src, void* dst, size_t n);
    void read_block(void* dst, const void* src, size_t n);
    void save_configuration(DosingConfiguration cfg);
    void get_configuration(DosingConfiguration* cfg, uint8_t id);
};

#endif