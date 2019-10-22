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

        #define ELROND_GPIO_DIO_TYPE ELROND_UINT16_TYPE
        #define ELROND_GPIO_AIO_TYPE ELROND_UINT16_TYPE
        #define ELROND_GPIO_SERVO_TYPE ELROND_UINT16_TYPE
        #define ELROND_GPIO_PWM_TYPE ELROND_UINT16_TYPE

        #define STR(S) S

        // Module Definition
        #define DEFINE_MODULE(CLASS)    elrond::interfaces::RuntimeInterface * elrond::__rtInstance__ = NULL;\
                                        extern "C" void _setAppInstance(elrond::interfaces::RuntimeInterface *app){elrond::__rtInstance__ = app;}\
                                        extern "C" elrond::interfaces::ModuleInterface *_getInstance(){return (elrond::interfaces::ModuleInterface*) new CLASS();}\
                                        extern "C" void _deleteInstance(CLASS *obj){ delete obj; }\
                                        extern "C" const char * _infoMainClassName(){return #CLASS;}\
                                        extern "C" int _infoApiVersion(){return ELROND_API_VERSION;}\
                                        extern "C" int _infoApiRevision(){return ELROND_API_REVISION;}

        #define DEFINE_MODULE_PRETTY_NAME(NAME) extern "C" const char *  _infoPrettyName(){return NAME;}
        #define DEFINE_MODULE_AUTHOR_NAME(NAME) extern "C" const char *  _infoAuthorName(){return NAME;}
        #define DEFINE_MODULE_AUTHOR_EMAIL(EMAIL) extern "C" const char *  _infoAuthorEmail(){return EMAIL;}
        #define DEFINE_MODULE_VERSION(VERSION) extern "C" const char *  _infoVersion(){return VERSION;}

    #elif defined ARDUINO_ARCH_AVR

        // Includes
        #include "Arduino.h"

        #if defined ARDUINO_ARCH_AVR
            #include "Servo.h"
        #endif

        // Defines
        #define STR(S) F(S)
        #define USE_LINKED_NODES
        #define WITHOUT_DESTRUCTORS

        // Generic macro for platforms that uses Arduino IDE
        #define INO_PLATFORM

        // Typedefs
        #if defined ARDUINO_ARCH_AVR

            #define ELROND_INT8_TYPE char
            #define ELROND_UINT8_TYPE unsigned char
            #define ELROND_INT16_TYPE int
            #define ELROND_UINT16_TYPE unsigned int
            #define ELROND_INT32_TYPE long
            #define ELROND_UINT32_TYPE unsigned long

            #define ELROND_GPIO_DIO_TYPE ELROND_UINT8_TYPE
            #define ELROND_GPIO_AIO_TYPE ELROND_UINT16_TYPE
            #define ELROND_GPIO_SERVO_TYPE Servo
            #define ELROND_GPIO_PWM_TYPE ELROND_UINT16_TYPE

        #endif

        // Module Definition
        #define DEFINE_MODULE(CLASS)
        #define DEFINE_MODULE_PRETTY_NAME(NAME)
        #define DEFINE_MODULE_AUTHOR_NAME(NAME)
        #define DEFINE_MODULE_AUTHOR_EMAIL(EMAIL)
        #define DEFINE_MODULE_VERSION(VERSION)

        #undef highByte
        #undef lowByte
        #undef word
        #undef INPUT
        #undef abs

    #else
        #error "Incompatible Platform."
    #endif

#endif
