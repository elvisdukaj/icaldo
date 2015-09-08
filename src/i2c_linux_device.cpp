#include "i2c_linux_device.h"

#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <stdexcept>
#include <sstream>
#include <iostream>

#include <cstring>

using namespace std;

namespace i2c {
namespace linux {

device::device(const string& dev, address_t address )
    : mDevice{ open( dev.c_str(), O_RDWR, 0 ) },
      mAddress( address )
{
    if( mDevice == -1 )
    {
        ostringstream os;
        os << "Unable to open " << dev << ": " << strerror( errno );
        throw invalid_argument{std::move( os.str() ) };
    }
}

device::~device()
{
    close( mDevice );
}


void device::write( const buffer_t& data )
{
    setAddress();
    if( ::write(mDevice, data.data(), data.size()) < 0 )
    {
        ostringstream os;
        os << "unable to write: " << strerror( errno );
        throw runtime_error{ move( os.str() ) };
    }
}


void device::write( std::initializer_list< uint8_t > data )
{
    setAddress();

    if( ::write(mDevice, begin( data ), data.size()) < 0 )
    {
        ostringstream os;
        os << "unable to write: " << strerror( errno );
        throw runtime_error{ move( os.str() ) };
    }
}

buffer_t device::read( size_t len ) const
{
    setAddress();
    buffer_t data( len );

    auto res = ::read( mDevice, data.data(), data.size() );

    if( res < 0 )
    {
        ostringstream os;
        os << "unable to read: " << strerror( errno );
        throw runtime_error{ move( os.str() ) };
    }

    return data;
}

void device::setAddress() const
{
    // set the address
    if( ioctl( mDevice, I2C_SLAVE, mAddress ) < 0 )
    {
        ostringstream os;
        os << "unable to set i2c address: " << strerror( errno );
        throw runtime_error{ move( os.str() ) };
    }
}

} // linux
} // i2c
