#ifndef WIRE_1_H
#define WIRE_1_H

#include <string>
#include <memory>

struct Celsius
{
    long double val;

    operator long double() const
    {
        return val;
    }

    Celsius& operator += ( long double v )
    {
        val += v;
        return *this;
    }

    Celsius& operator -= ( long double v )
    {
        val -= v;
        return *this;
    }
};

constexpr Celsius operator"" _celsius( long double val)
{
    return Celsius{ val };
}

namespace wire_1 {

class Idevice {
public:
    virtual ~Idevice() = 0;

    virtual Celsius read() const = 0;
};

// factory function
using device_t = std::unique_ptr< Idevice >;
device_t create( const std::string& serial );

} // wire_1

#endif // WIRE_1_H

