#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include "i2c_type.h"

#include <string>
#include <memory>
#include <initializer_list>

namespace i2c {


// interface for a generic i2c device
class Idevice
{
public:
    virtual ~Idevice() = 0;

    virtual void write( const buffer_t& data ) = 0;
    virtual void write( std::initializer_list< uint8_t > data) = 0;
    virtual buffer_t read( size_t len = 1 ) const = 0;
};

// factory function
using device_t = std::unique_ptr< Idevice >;
device_t create( const std::string& devname, address_t address );

} // i2c

#endif // I2C_DEVICE_H

