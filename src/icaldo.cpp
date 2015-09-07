#include "mcp4725.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    string device{"/dev/i2c-1"};

    try
    {
        int address = 0x62;
        cout << "opening at address " << hex << address << dec << endl;
        dac::mcp4725 d1( device, address);
        cout << "done..." << endl;
        for( double v : { 0.1, 0.5, 1.0, 3.0, 4.0, 4.5, 5.0 } )
        {
            cout << "setting v to " << v << "...";
            d1.set( v );
            string line;
            getline( cin, line );
            cout << "done..." << endl;
        }


        address = 0x63;
        cout << "opening at address " << hex << address << dec << endl;
        dac::mcp4725 d2( device, address);
        cout << "done..." << endl;
        for( double v : { 0.1, 0.5, 1.0, 3.0, 4.0, 4.5, 5.0 } )
        {
            cout << "setting v to " << v << "...";
            d2.set( v );
            string line;
            getline( cin, line );
            cout << "done..." << endl;
        }
    }
    catch( const std::exception& exc )
    {
        cerr << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}
