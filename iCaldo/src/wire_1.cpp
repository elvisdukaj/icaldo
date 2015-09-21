#include "wire_1_linux.h"

namespace wire_1 {

Idevice::~Idevice() {}


device_t create( const std::string& serial )
{
    return device_t{ new linux::device{ serial } };
}

} // i2c
