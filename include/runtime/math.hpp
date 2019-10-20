#if !defined  _ELROND_MATH_HPP
#define _ELROND_MATH_HPP

    #include "types.hpp"

    namespace elrond {

        /* Based in Arduino map funtion */
        long map(long x, long in_min, long in_max, long out_min, long out_max);

        int abs(int v);
        long int abs (long int v);

        double mod(double v);

        template <class T> void swap(T &v1, T &v2){
            T t = v1;
            v1 = v2;
            v2 = t;
        }
    }
#endif
