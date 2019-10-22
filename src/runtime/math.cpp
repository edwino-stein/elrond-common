#include "runtime/math.hpp"

#if defined GENERIC_STD_PLATFORM
    #include <cmath>
#endif

/* ******************************** Math Util ******************************** */

long elrond::map(long x, long in_min, long in_max, long out_min, long out_max){
    #if defined GENERIC_STD_PLATFORM
        // Based in Arduino map funtion
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    #elif defined INO_PLATFORM
        return ::map(x, in_min, in_max, out_min, out_max);
    #endif
}

int elrond::abs(int v){
    #if defined GENERIC_STD_PLATFORM
        return ::abs(v);
    #elif defined INO_PLATFORM
        return ((v) > 0 ? (v) : -(v));
    #endif
}

long int elrond::abs(long int v){
    #if defined GENERIC_STD_PLATFORM
        return ::abs(v);
    #elif defined INO_PLATFORM
        return ((v) > 0 ? (v) : -(v));
    #endif
}

double elrond::mod(double v){
    #if defined GENERIC_STD_PLATFORM
        return ::modf(v, nullptr);
    #elif defined INO_PLATFORM
        #if ARDUINO_ARCH_AVR
            return modf(v, nullptr);
        #elif defined ESP_PLATFORM
            return v - ((int) v);
        #endif
    #endif
}
