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


class IThermometer {
public:
    virtual ~IThermometer() = 0;

    virtual Celsius read() const = 0;
};

// factory function
using IThermometerPtr = std::unique_ptr< IThermometer >;
IThermometerPtr CreateThermomether( const std::string& serial );


#endif // WIRE_1_H

