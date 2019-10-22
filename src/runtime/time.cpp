#include "runtime/time.hpp"

#if defined GENERIC_STD_PLATFORM
    #include <chrono>
    #include <thread>
#endif

/* *********************************** Time ********************************** */

unsigned long elrond::millis(){
    #if defined GENERIC_STD_PLATFORM
        auto duration = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    #elif defined INO_PLATFORM
        return ::millis();
    #endif
}

unsigned long elrond::micros(){
    #if defined GENERIC_STD_PLATFORM
        auto duration = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    #elif defined INO_PLATFORM
        return ::micros();
    #endif
}

void elrond::delay(unsigned long ms){
     #if defined GENERIC_STD_PLATFORM
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    #elif defined INO_PLATFORM
        ::delay(ms);
    #endif
}

void elrond::delayMicroseconds(unsigned int us){
     #if defined GENERIC_STD_PLATFORM
        std::this_thread::sleep_for(std::chrono::microseconds(us));
    #elif defined INO_PLATFORM
        ::delayMicroseconds(us);
    #endif
}
