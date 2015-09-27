#ifndef I2C_TYPE_H
#define I2C_TYPE_H

#include <cstdint>
#include <vector>

namespace i2c {

using address_t = int;
using buffer_t = std::vector< uint8_t >;

} // i2c

#endif // I2C_TYPE_H
