#ifndef ELROND_PLATFORM_STD_HPP
    #define ELROND_PLATFORM_STD_HPP

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

        #define ELROND_WINDOWS_PLATFORM

        #ifdef _WIN64
            #define ELROND_WINDOWS_64_PLATFORM
        #else
            #define ELROND_WINDOWS_32_PLATFORM
        #endif

        #error "Incompatible Windows Platform."

    #elif __APPLE__

        #include <TargetConditionals.h>
        #define ELROND_APPLE_PLATFORM

        #if TARGET_OS_MAC
            #define ELROND_MACOS_PLATFORM
        #else
            #error "Incompatible Apple Platform."
        #endif

    #elif __linux__
        #define ELROND_LINUX_PLATFORM
    #else
        #error "Incompatible Platform"
    #endif

    #define ELROND_STD_PLATFORM

    // #define ELROND_DISABLE_DESTRUCTORS

    #ifdef ELROND_DISABLE_DESTRUCTORS
        #define ELROND_DEFAULT_DESTRUCTOR delete
    #else
        #define ELROND_DEFAULT_DESTRUCTOR default
    #endif

    #ifdef ELROND_DISABLE_INLINE
        #define ELROND_INLINE
    #else
        #define ELROND_INLINE inline
    #endif

    #include "elrond_version.hpp"

    #include <iostream>
    #include <cmath>
    #include <chrono>
    #include <thread>
    #include <cstdint>
    #include <string>
    #include <functional>
    #include <exception>

    // Util macros
    #define _ELROND_TO_STR(M) #M
    #define ELROND_TO_STR(M) _ELROND_TO_STR(M)
    #define ELROND_TO_STR_CONCAT(...) _ELROND_TO_STR(__VA_ARGS__)

    // External module API
    #define ELROND_MOD_GET_API_VERSION_FUNC_NAME    __elrond_get_api_version__
    #define ELROND_MOD_GET_FACTORY_FUNC_NAME        __elrond_get_module_factory__
    #define ELROND_MOD_NUM_TYPE                     elrond::dWord
    #define ELROND_MOD_FACTORY_TYPE                 elrond::platform::FactoryInterface*

    #ifndef ELROND_ENABLE_EXTERNAL_API_SETUP
        #define ELROND_DEFINE_MODULE(...)
        #define ELROND_DEFINE_DEFAULT_MODULE(...)
    #endif

#endif
