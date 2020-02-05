#if !defined  _ELROND_MATH_HPP
#define _ELROND_MATH_HPP

    #include "types.hpp"

    namespace elrond {

        /* Based in Arduino map funtion */
        long map(const long x, const long inMin, const long inMax, const long outMin, const long outMax);

        int abs(const int v);
        long int abs (const long int v);

        double mod(const double v);
        template <class T> void swap(T &v1, T &v2);
    }

#endif
