#include "mcp4725.h"
#include <cmath>

#include <iostream>
#include <iomanip>

namespace dac {


enum class commands : uint8_t
{
    write_dac               = 0x40,
    write_dac_and_eeprom    = 0x60
};


mcp4725::mcp4725(
        std::string devname,
        i2c::address_t address,
        double vdd
        )
    : mDevice{ i2c::smbus::create( devname, address ) },
      mVDD{ vdd }
{
}


void mcp4725::set(double val, bool writeToEEPROM)
{
    // convert val into
    auto d = voltageToRegister( val );

    std::cout << "setting register to " << std::hex << d << std::dec << std::endl;

    if( writeToEEPROM )
    {
        mDevice->write(
                static_cast< i2c::smbus::command_t >( commands::write_dac_and_eeprom ),
                {
                    static_cast< uint8_t >( ( d >> 4 ) & 0xff ),
                    static_cast< uint8_t >( ( d << 4 ) & 0xFF )
                }
                );
    }
    else
    {
        mDevice->write(
                static_cast< i2c::smbus::command_t >( commands::write_dac ),
                {
                    static_cast< uint8_t >( ( d >> 4 ) & 0xff ),
                    static_cast< uint8_t >( ( d << 4 ) & 0xFF )
                }
                );
    }
}

double mcp4725::get() const
{
}

int mcp4725::voltageToRegister( double Vout )
{

    //       4096
    // K = ------
    //       Vdd

    // D = Vout * K

    static const auto K = 4096.0 / mVDD;
    return static_cast< int >( round( Vout * K ) );
}

} // dac
