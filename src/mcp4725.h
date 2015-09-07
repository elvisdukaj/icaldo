#ifndef MCP4725
#define MCP4725

#include "smbus_device.h"

namespace dac {

class mcp4725
{
public:
    mcp4725(
            std::string devname,
            i2c::address_t address,
            double vdd = 5.0
            );

    void set( double val, bool writeToEEPROM = false );
    double get() const;

private:
    int voltageToRegister( double voltage );

private:
    i2c::smbus::device_t mDevice;
    const double mVDD = 5.0;          // Volt
};

} // dac

#endif // MCP4725

