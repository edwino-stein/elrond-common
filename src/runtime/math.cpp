#include "runtime/math.hpp"

/*  ****************************************************************************
    ******************* Elrond math functions implementation *******************
    ****************************************************************************/

// Based in Arduino map funtion
long elrond::map(const long x, const long inMin, const long inMax, const long outMin, const long outMax)
{ return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin; }

int elrond::abs(int v)
{ return ::abs(v); }

long int elrond::abs(long int v)
{ return ::abs(v); }

double elrond::mod(double v)
{
    double i;
    return ::modf(v, &i);
}
