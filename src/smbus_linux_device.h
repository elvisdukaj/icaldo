#ifndef SMBUS_LINUX_DEVICE_H
#define SMBUS_LINUX_DEVICE_H

#include "smbus_device.h"

namespace i2c {
namespace smbus {
namespace linux {

class device : public Idevice
{
public:
    device( const std::string& dev, address_t address );
    ~device();

    void write( command_t command, const buffer_t& data ) override;
    void write( command_t command, std::initializer_list< uint8_t > data) override;

    buffer_t read( command_t command, size_t len = 1 ) const override;

private:
    void setAddress() const;

private:
    const int mDevice;
    const address_t mAddress;
};

} // linux
} // smbus
} // i2c

#endif // SMBUS_LINUX_DEVICE_H

