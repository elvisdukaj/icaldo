#include "i2c_linux_device.h"

namespace i2c {

Idevice::~Idevice() {}

device_t create( const std::string& devname, address_t address )
{
//    return make_unique< Idevice >( new linux::device( devname, address ) );
    return device_t{ new linux::device( devname, address ) };
}

} // i2c
