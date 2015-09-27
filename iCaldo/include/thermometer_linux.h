#ifndef WIRE_1_LINUX_H
#define WIRE_1_LINUX_H

#include "thermometer.h"

namespace linux {

class Thermomether : public IThermometer {
public:
    Thermomether( const std::string& serial );
    ~Thermomether() {};

    Celsius read() const override;

private:
    const std::string mDevice;
};

} // linux
#endif // WIRE_1_LINUX_H

