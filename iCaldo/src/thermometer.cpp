#include "thermometer_linux.h"

IThermometer::~IThermometer() {}

IThermometerPtr CreateThermomether( const std::string& serial )
{
    return IThermometerPtr{ new linux::Thermomether{ serial } };
}
