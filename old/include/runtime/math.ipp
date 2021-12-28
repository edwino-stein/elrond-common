#if !defined  _ELROND_MATH_IPP
#define _ELROND_MATH_IPP

    #include "runtime/math.hpp"

    namespace elrond {
        template <class T> void swap(T &v1, T &v2){
            T t = v1;
            v1 = v2;
            v2 = t;
        }
    }

#endif
