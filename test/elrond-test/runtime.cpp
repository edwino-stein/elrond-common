#include <cmath>
#include <chrono>
#include <thread>

#include "runtime/bitwise.hpp"
#include "runtime/math.hpp"
#include "runtime/time.hpp"

/* ********************************** Bitwise ********************************* */

elrond::byte elrond::highByte(const elrond::word data)
{
    return (elrond::byte) (data >> 8);
}

elrond::byte elrond::lowByte(const elrond::word data)
{
    return (elrond::byte) (data & 0x00FF);
}

elrond::word elrond::makeWord(const elrond::byte high, const elrond::byte low)
{
    return (elrond::word) ((high << 8) | (low & 0x00FF));
}

elrond::word elrond::highWord(const elrond::dWord data)
{
    return (elrond::word) (data >> 16);
}

elrond::word elrond::lowWord(const elrond::dWord data)
{
    return (elrond::word) (data & 0x0000FFFF);
}

elrond::dWord elrond::makeDWord(const elrond::word high, elrond::word low)
{
    return (elrond::dWord) ((((elrond::dWord) high) << 16) | (low & 0x0000FFFF));
}

/* *********************************** Math *********************************** */

long elrond::map(long x, long in_min, long in_max, long out_min, long out_max)
{
    // Based in Arduino map funtion
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int elrond::abs(int v)
{
    return ::abs(v);
}

long int elrond::abs(long int v)
{
    return ::abs(v);
}

double elrond::mod(double v)
{
    double i;
    return ::modf(v, &i);
}

/* *********************************** Time ********************************** */

unsigned long elrond::millis()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

unsigned long elrond::micros()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

void elrond::delay(unsigned long ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void elrond::delayMicroseconds(unsigned int us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
