#ifndef SMBUS_DEVICE_H
#define SMBUS_DEVICE_H

#include "i2c_type.h"

#include <string>
#include <memory>
#include <initializer_list>

namespace i2c { namespace smbus {

using address_t = int;
using buffer_t = std::vector< uint8_t >;
using command_t = int;

// interface for a generic i2c device
class Idevice {
public:
    virtual ~Idevice() = 0;

    virtual void write( command_t command, const buffer_t& data ) = 0;
    virtual void write(  command_t command, std::initializer_list< uint8_t > data) = 0;
    virtual buffer_t read(  command_t command, size_t len = 1 ) const = 0;
};

// factory function
using device_t = std::unique_ptr< Idevice >;
device_t create( const std::string& devname, address_t address );

} } // smbus i2c

#endif // SMBUS_DEVICE_H

