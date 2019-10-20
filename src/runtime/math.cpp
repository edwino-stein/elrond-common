#include "runtime/math.hpp"

#if defined GENERIC_STD_PLATFORM
    #include <cmath>
#endif

/* ******************************** Math Util ******************************** */

long elrond::map(long x, long in_min, long in_max, long out_min, long out_max){
    // Based in Arduino map funtion
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int elrond::abs(int v){
    #if defined GENERIC_STD_PLATFORM
        return ::abs(v);
    #endif
}

long int elrond::abs(long int v){
    #if defined GENERIC_STD_PLATFORM
        return ::abs(v);
    #endif
}

double elrond::mod(double v){
    #if defined GENERIC_STD_PLATFORM
        return ::modf(v, nullptr);
    #endif
}
