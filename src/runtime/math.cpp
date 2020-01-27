#include "runtime/math.hpp"

/*  ****************************************************************************
    ******************* Elrond math functions implementation *******************
    ****************************************************************************/

namespace elrond {

    // Based in Arduino map funtion
    ELROND_INLINE_FUNC long map(
        const long x,
        const long inMin,
        const long inMax,
        const long outMin,
        const long outMax
    ){ return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin; }

    ELROND_INLINE_FUNC int abs(int v)
    { return ::abs(v); }

    ELROND_INLINE_FUNC long int abs(long int v)
    { return ::abs(v); }

    ELROND_INLINE_FUNC double mod(double v)
    {
        double i;
        return ::modf(v, &i);
    }
}
