/*
    Copyright 2019 Edwino A. L. Stein

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#if !defined  _ELROND_PLATFORM_HPP
    #define _ELROND_PLATFORM_HPP

    #include "version.hpp"

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

        #define GENERIC_STD_PLATFORM
        #define WINDOWS_PLATFORM

        #ifdef _WIN64
            #define WINDOWS_64_PLATFORM
        #else
            #define WINDOWS_32_PLATFORM
        #endif

        #error "Incompatible Windows Platform."

    #elif __APPLE__

        #include <TargetConditionals.h>

        #define GENERIC_STD_PLATFORM
        #define APPLE_PLATFORM

        #if TARGET_OS_MAC
            #define MACOS_PLATFORM
        #else
            #error "Incompatible Apple Platform."
        #endif

    #elif __linux__

        #define GENERIC_STD_PLATFORM
        #define LINUX_PLATFORM

    #else
        #error "Incompatible Platform"
    #endif

    /* *********************************************************************** */
    /* ******************* Generic Platform with STD LIBCPP ****************** */
    /* *********************************************************************** */

    // Build Options
    #define ELROND_WITH_MODULES_INFO
    #define ELROND_WITH_DESTRUCTORS
    #define ELROND_WITH_STR_TYPE
    #define ELROND_WITH_LAMBDA_TYPE
    // #define ELROND_WITH_INLINE_FUNC
    // #define ELROND_WITH_LINKED_NODES

    // Includes
    #include <iostream>
    #include <cmath>
    #include <chrono>
    #include <thread>

    #ifdef ELROND_WITH_STR_TYPE
        #include <string>
    #endif

    #ifdef ELROND_WITH_LAMBDA_TYPE
        #include <functional>
    #endif

    // Constants
    #define HIGH_VALUE 0xFFFF
    #define LOW_VALUE 0x0

    // Typedefs
    #define ELROND_INT8_TYPE char
    #define ELROND_UINT8_TYPE unsigned char
    #define ELROND_INT16_TYPE short
    #define ELROND_UINT16_TYPE unsigned short
    #define ELROND_INT32_TYPE int
    #define ELROND_UINT32_TYPE unsigned int

    #define ELROND_SIZE_TYPE std::size_t
    #define ELROND_TIME_TYPE unsigned long long

    #define ELROND_GPIO_DIO_TYPE ELROND_UINT16_TYPE
    #define ELROND_GPIO_AIO_TYPE ELROND_UINT16_TYPE
    #define ELROND_GPIO_SERVO_TYPE ELROND_UINT16_TYPE
    #define ELROND_GPIO_PWM_TYPE ELROND_UINT16_TYPE

    #ifdef ELROND_WITH_STR_TYPE
        #define ELROND_STR_TYPE std::string
        #define ELROND_STR(S) ELROND_STR_TYPE(S)
    #else
        #define ELROND_STR(S) S
    #endif

    #ifdef ELROND_WITH_LAMBDA_TYPE
        #define ELROND_LAMBDA_TYPE std::function
        #define ELROND_LAMBDA_FUNC(R, ...) ELROND_LAMBDA_TYPE < R ( __VA_ARGS__ ) >
    #else
        #define ELROND_LAMBDA_FUNC(R, ...) R (*)( __VA_ARGS__ )
    #endif

    #ifdef ELROND_WITH_INLINE_FUNC
        #define ELROND_INLINE_FUNC inline
    #else
        #define ELROND_INLINE_FUNC
    #endif

    // Module Definition
    #define DEFINE_MODULE(CLASS)    elrond::interface::Runtime* elrond::__rtInstance__ = NULL;\
                                    extern "C" void _setAppInstance(elrond::interface::Runtime* app){elrond::__rtInstance__ = app;}\
                                    extern "C" elrond::interface::Module* _getInstance(){return (elrond::interface::Module*) new CLASS();}\
                                    extern "C" void _deleteInstance(CLASS *obj){ delete obj; }\
                                    extern "C" const char * _infoMainClassName(){return #CLASS;}\
                                    extern "C" int _infoApiVersion(){return ELROND_API_VERSION;}\
                                    extern "C" int _infoApiRevision(){return ELROND_API_REVISION;}

    #define DEFINE_MODULE_PRETTY_NAME(NAME) extern "C" const char *  _infoPrettyName(){return NAME;}
    #define DEFINE_MODULE_AUTHOR_NAME(NAME) extern "C" const char *  _infoAuthorName(){return NAME;}
    #define DEFINE_MODULE_AUTHOR_EMAIL(EMAIL) extern "C" const char *  _infoAuthorEmail(){return EMAIL;}
    #define DEFINE_MODULE_VERSION(VERSION) extern "C" const char *  _infoVersion(){return VERSION;}
    #define ELROND_MOD_INFO_APP_P elrond::interface::Runtime*
    #define ELROND_MOD_APP_VAR_N __rt_instance__
    #define ELROND_MOD_APP_VAR elrond::ELROND_MOD_APP_VAR_N

#endif
