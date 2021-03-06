#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include "i2c_type.h"

#include <string>
#include <memory>
#include <initializer_list>

namespace i2c {


// interface for a generic i2c device
class Ii2c
{
public:
    virtual ~Ii2c() = 0;

    virtual void write( const buffer_t& data ) = 0;
    virtual void write( std::initializer_list< uint8_t > data) = 0;
    virtual buffer_t read( size_t len = 1 ) const = 0;
};

// factory function
using Ii2cPtr = std::unique_ptr< Ii2c >;
Ii2cPtr create( const std::string& devname, address_t address );

} // i2c

#endif // I2C_DEVICE_H

