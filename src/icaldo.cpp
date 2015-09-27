#include "mcp4725.h"
#include <iostream>
#include <iomanip>

using namespace std;

inline void WaitUser( bool showMessage = false)
{
    static string line;
    // wait for 'Enter'
    cout << "Press 'Enter' to continue" << endl;
    getline( cin, line );
}

int main()
{
    string device{"/dev/i2c-1"};

    try
    {
        for( auto address : { 0x62, 0x63 } )
        {
            cout << "Opening dac at address " << hex << address << dec << endl;
            dac::mcp4725 dev( device, address );

            cout << "STARTIN VOLTAGE TEST" << endl;
            for( auto v : { 0.1_V, 0.5_V, 1.0_V, 3.0_V, 4.0_V, 4.5_V, 5.0_V } )
            {
                dev.set( v );
                cout << "setting voltage to " << v << "V" << endl;
                WaitUser();
            }
            cout << "TEST FINISHED" << endl;

            cout << "STARTIN PERCENTAGE TEST" << endl;
            for( auto v : { 0.0_percent, 0.1_percent, 0.5_percent, 100.0_percent } )
            {
                dev.set( v );
                cout << "setting voltage to " << v * 100.0 << "%" << endl;
                WaitUser();
            }

            cout << endl;
        }
    }
    catch( const std::exception& exc )
    {
        cerr << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}
