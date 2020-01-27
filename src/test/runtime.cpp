#include <chrono>
#include <thread>

#include "runtime/time.hpp"

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
