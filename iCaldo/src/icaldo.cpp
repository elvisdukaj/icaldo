#include "mcp4725.h"

#define BOOST_TEST_MODULE DAC_TEST
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>

#include <thread>

using namespace std;

BOOST_AUTO_TEST_CASE( dac63_0Volt )
{
    BOOST_LOG_TRIVIAL( trace ) << "DAC VOLTAGE TEST - 0 Volt";
    dac::mcp4725 d{"/dev/i2c-1", 0x63};
    auto const targetVal = 0.0_V;

    d.set( targetVal );
    auto settedVal = d.getVolt();
    d.state();

    BOOST_CHECK_EQUAL( targetVal, settedVal );
}


BOOST_AUTO_TEST_CASE( dac63_2Volt )
{
    BOOST_LOG_TRIVIAL( trace ) << "DAC VOLTAGE TEST - 2 Volt";
    dac::mcp4725 d{"/dev/i2c-1", 0x63};
    auto const targetVal = 2.0_V;

    d.set(targetVal);
    auto settedVal = d.getVolt();
    d.state();

    BOOST_CHECK_EQUAL( targetVal, settedVal );
}

BOOST_AUTO_TEST_CASE( dac63_5Volt )
{
    BOOST_LOG_TRIVIAL( trace ) << "DAC VOLTAGE TEST - 5 Volt";
    dac::mcp4725 d{"/dev/i2c-1", 0x63};
    auto const targetVal = 5.0_V;

    d.set( targetVal );
    auto settedVal = d.getVolt();
    d.state();

    BOOST_CHECK_EQUAL( targetVal, settedVal );
}


BOOST_AUTO_TEST_CASE( dac63_100Perc )
{
    BOOST_LOG_TRIVIAL( trace ) << "DAC VOLTAGE TEST - 100%";
    dac::mcp4725 d{"/dev/i2c-1", 0x63};
    auto const targetVal = 1.0_percent;

    d.state();
    d.set(targetVal);
    auto settedVal = d.getPercent();
    d.state();

    BOOST_CHECK_EQUAL( targetVal, settedVal );
}


BOOST_AUTO_TEST_CASE( dac63_100PercToEEPROM )
{
    BOOST_LOG_TRIVIAL( trace ) << "DAC VOLTAGE TEST TO EEPROM - 100%";
    dac::mcp4725 d{"/dev/i2c-1", 0x63};
    auto const targetVal = 1.0_percent;

    d.state();
    d.set(targetVal, true);
    auto settedVal = d.getPercent();

    BOOST_REQUIRE_EQUAL( d.state(), dac::mcp4725::BUSY );
    BOOST_LOG_TRIVIAL( trace ) << "Waiting 3s";
    this_thread::sleep_for( chrono::seconds{ 3 } );
    BOOST_REQUIRE_EQUAL( d.state(), dac::mcp4725::READY );

    BOOST_CHECK_EQUAL( targetVal, settedVal );
}

