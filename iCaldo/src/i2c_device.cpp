#include "i2c_linux_device.h"

namespace i2c {

Ii2c::~Ii2c() {}

Ii2cPtr create( const std::string& devname, address_t address )
{
    return Ii2cPtr{ new linux::i2c{ devname, address } };
}

} // i2c
