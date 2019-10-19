#if !defined  _ELROND_PLATFORM_HPP
    #define _ELROND_PLATFORM_HPP

    #include "version.hpp"

    /* *********************************************************************** */
    /* ************************* Platform definitions ************************ */
    /* *********************************************************************** */

    #define HIGH_VALUE 0xFFFF
    #define LOW_VALUE 0x0

    #if defined GENERIC_STD_PLATFORM

        /* ***************** Generic Platform with STD LIBCPP ***************** */

        // Includes
        #include <iostream>

        // Typedefs
        #define ELROND_INT8_TYPE char
        #define ELROND_UINT8_TYPE unsigned char
        #define ELROND_INT16_TYPE short
        #define ELROND_UINT16_TYPE unsigned short
        #define ELROND_INT32_TYPE int
        #define ELROND_UINT32_TYPE unsigned int

    #else
        #error "Incompatible Platform."
    #endif

#endif
