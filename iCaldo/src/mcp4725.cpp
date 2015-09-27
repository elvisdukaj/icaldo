#include "mcp4725.h"
#include <boost/log/trivial.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

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
    setRegister( writeToEEPROM, voltageToRegister( val ) );
}

void mcp4725::set( Percent val, bool writeToEEPROM )
{
    // convert val into
    setRegister( writeToEEPROM, percentToRegister( val ) );
}

mcp4725::State mcp4725::state() const
{
    auto res = mDevice->read(5);

    BOOST_LOG_TRIVIAL( trace ) << "reading state: {"
                               << (int)res[0] << ' '
                               << (int)res[1] << ' '
                               << (int)res[2] << ' '
                               << (int)res[3] << ' '
                               << (int)res[4] << "} ";

    return res[ 0 ] >> 7 ? State::BUSY : State::READY;
}

Percent mcp4725::getPercent() const
{
    return registerToPercent( getRegister() );
}

Volt mcp4725::getVolt() const
{
    return registerToVolt( getRegister() );
}

void mcp4725::setRegister(bool writeToEEPROM, int val)
{
    auto cmd = writeToEEPROM ? commands::write_dac_and_eeprom : commands::write_dac;

    BOOST_LOG_TRIVIAL( trace ) << "writing " << hex << setfill('0')
                               << setw( 2 ) << (int) cmd << ", "
                               << setw( 2 ) << val
                               << dec << setfill(' ');

    mDevice->write(
    {
        static_cast< uint8_t >( cmd ),
        static_cast< uint8_t >( ( val >> 4 ) & 0xFF ),
        static_cast< uint8_t >( ( val << 4 ) & 0xFF )
    }
    );
}

int mcp4725::getRegister() const
{
    auto res = mDevice->read( 5 );
    auto reg = res[2] << 4 | res[1];

    BOOST_LOG_TRIVIAL( trace ) << "reading register "
                               << hex << setfill('0')
                               << setw( 2 ) << reg
                               << dec << setfill(' ');
    return reg;
}

int mcp4725::voltageToRegister( long double Vout ) const
{
    //       4096
    // K = ------
    //       Vdd

    // D = Vout * K

    static const auto K = mMaxValue / mVDD;
    return static_cast< int >( round( Vout * K ) );
}


int mcp4725::percentToRegister( long double perc ) const
{
    // percent : 100 = x : mMaxValue
    // x = percent * 4096 / 100
    return round( perc * mMaxValue );
}

Percent mcp4725::registerToPercent( int reg ) const
{
    // percent : 100 = x : 4096
    // p = 100 * x / 4096
    static const auto k = 100.0L / mMaxValue;
    return  Percent{round( reg * k) / 100.0L };
}

Volt mcp4725::registerToVolt( int reg ) const
{
    //        Vdd x reg
    // Vout = ---------
    //         4096.0

    long double K = mVDD / mMaxValue;
    return Volt{ round( reg * K ) };
}

} // dac
