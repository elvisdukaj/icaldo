#ifndef MCP4725
#define MCP4725

#include "i2c_device.h"

struct Volt
{
    long double val;

    operator long double() const
    {
        return val;
    }
};

struct Percent
{
    long double val;

    operator long double() const
    {
        return val;
    }
};


constexpr Percent operator"" _percent( long double val)
{
    return Percent{ val };
}

constexpr Volt operator"" _V( long double val )
{
    return Volt{ val };
}

namespace dac {

class mcp4725
{
public:
    mcp4725(
            std::string devname,
            i2c::address_t address
            );

    void set( Volt val, bool writeToEEPROM = false );
    void set( Percent val, bool writeToEEPROM = false );
    double get() const;

private:
    int voltageToRegister( long double voltage );
    int percentToRegister( long double percent );

private:
    i2c::device_t mDevice;
    double mVDD = 5.0;          // Volt
};

} // dac

#endif // MCP4725

