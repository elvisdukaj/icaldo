#include "mcp4725.h"
#include <cmath>

namespace dac {

enum class commands : uint8_t
{
    write_dac               = 0x40,
    write_dac_and_eeprom    = 0x60
};


mcp4725::mcp4725(
        std::string devname,
        i2c::address_t address
        )
    : mDevice{ i2c::create( devname, address ) }
{
    mVDD = 5.0;
}


void mcp4725::set(Volt val, bool writeToEEPROM)
{
    // convert val into
    auto d = voltageToRegister( val );

    mDevice->write(
    {
        writeToEEPROM ?
            static_cast< uint8_t >( commands::write_dac_and_eeprom ) :
            static_cast< uint8_t >( commands::write_dac),
        static_cast< uint8_t >( ( d >> 4 ) & 0xFF ),
        static_cast< uint8_t >( ( d << 4 ) & 0xFF )
    }
    );
}


void mcp4725::set( Percent val, bool writeToEEPROM )
{
    // convert val into
    auto d = percentToRegister( val );

    mDevice->write(
    {
        writeToEEPROM ?
        static_cast< uint8_t >(commands::write_dac_and_eeprom) :
        static_cast< uint8_t >(commands::write_dac),
        static_cast< uint8_t >((d >> 4) & 0xFF),
        static_cast< uint8_t >((d << 4) & 0xFF)
    }
    );
}

double mcp4725::get() const
{
    return 0.0;
}

int mcp4725::voltageToRegister( long double Vout )
{

    //       4096
    // K = ------
    //       Vdd

    // D = Vout * K

    static const auto K = 4095.0 / mVDD;
    return static_cast< int >( round( Vout * K ) );
}


int mcp4725::percentToRegister( long double perc )
{
    // percent : 100 = x : 4096
    // x = percent * 4096 / 100
    return round( perc * 4095.0L );
}

} // dac
