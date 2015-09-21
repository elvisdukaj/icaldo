#ifndef WIRE_1_LINUX_H
#define WIRE_1_LINUX_H

#include "wire_1.h"

namespace wire_1 {
namespace linux {

class device : public Idevice {
public:
    device( const std::string& serial );
    ~device() {};

    Celsius read() const override;

private:
    const std::string mDevice;
};

} // linux
} // wire_1

#endif // WIRE_1_LINUX_H

