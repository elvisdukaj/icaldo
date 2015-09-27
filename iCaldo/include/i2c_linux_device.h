#ifndef I2C_LINUX_DEVICE_H
#define I2C_LINUX_DEVICE_H

#include "i2c_device.h"

namespace i2c {
namespace linux {

class i2c : public Ii2c
{
public:
    i2c( const std::string& dev, address_t address );
    ~i2c() override;

    void write( const buffer_t& data ) override;
    void write( std::initializer_list< uint8_t > data) override;

    buffer_t read( size_t len = 1 ) const override;

private:
    void setAddress() const;

private:
    const int mDevice;
    const address_t mAddress;
};

} // linux
} // i2c

#endif // I2C_LINUX_DEVICE_H

