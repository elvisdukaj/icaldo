#include "thermometer_linux.h"

#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

namespace linux {

inline string CreatePath( const string& serial )
{
    ostringstream os;
    os << "/sys/bus/w1/devices/" << serial << "/w1_slave";
    return std::move( os.str() );
}

Thermomether::Thermomether( const std::string &serial )
    : mDevice{ CreatePath( serial ) }
{
}

Celsius Thermomether::read() const
{
    auto&& device = ifstream( mDevice );

    string line;
    vector< string > lines;
    while( getline( device, line ) )
           lines.emplace_back( line );

    if( lines.size() == 2 )
    {
        if( lines[0].find( string{"YES"} ) != string::npos )
        {
            static const string m{"t="};
            auto pos = lines[1].find( m );

            if( pos != string::npos )
            {
                auto temp_str = lines[ 1 ].substr( pos + m.size() );
                auto temp = stold( temp_str );
                return { temp / 1000.0L };
            }
        }
    }

    throw runtime_error{"Unable to read time"};
}

} // linux
