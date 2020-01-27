#include <cmath>
#include <chrono>
#include <thread>

#include "runtime/math.hpp"
#include "runtime/time.hpp"

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

elrond::timeT elrond::millis()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

elrond::timeT elrond::micros()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

void elrond::delay(const elrond::timeT ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void elrond::delayMicroseconds(const elrond::timeT us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
