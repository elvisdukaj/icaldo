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

    bool operator == ( const Volt& v ) const
    {
        return val == v.val;
    }

//    friend bool operator == ( const Volt& v1, const long double& v2 )
//    {
//        return v1.val == v2;
//    }

//    friend bool operator == ( const long double& v1, const Volt& v2 )
//    {
//        return v1 == v2.val;
//    }

//    friend bool operator < ( const Volt& v1, const long double& v2 )
//    {
//        return v1.val < v2;
//    }

//    friend bool operator < ( const long double& v1, const Volt& v2 )
//    {
//        return v1 < v2.val;
//    }
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

    enum State { READY = 0, BUSY };

    mcp4725(
            std::string devname,
            i2c::address_t address
            );

    void set( Volt val, bool writeToEEPROM = false );
    void set( Percent val, bool writeToEEPROM = false );

    State state() const;

    Percent getPercent() const;
    Volt getVolt() const;

private:
    void setRegister( bool writeToEEPROM, int val );
    int getRegister() const;

    int voltageToRegister( long double voltage ) const;
    int percentToRegister( long double percent ) const;
    Percent registerToPercent( int reg ) const;
    Volt registerToVolt( int reg ) const;

private:
    int mMaxValue = 4096 - 1;
    i2c::Ii2cPtr mDevice;
    double mVDD = 5.0L;
};

} // dac

#endif // MCP4725

