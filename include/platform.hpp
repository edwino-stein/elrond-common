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

    // Util macros
    #define _ELROND_TO_STR(M) #M
    #define ELROND_TO_STR(M) _ELROND_TO_STR(M)
    #define ELROND_TO_STR_CONCAT(...) _ELROND_TO_STR(__VA_ARGS__)

    // Module Definition
    #define ELROND_MOD_INFO_STR_T const char*
    #define ELROND_MOD_INFO_NUM_T ELROND_UINT32_TYPE
    #define ELROND_MOD_INFO_APP_P elrond::interface::Runtime*
    #define ELROND_MOD_INFO_MOD_P elrond::interface::Module*
    #define ELROND_MOD_APP_VAR_N __rt_instance__
    #define ELROND_MOD_APP_VAR elrond::ELROND_MOD_APP_VAR_N

    #define ELROND_MOD_SET_APP_FUNC_N __elrond_set_app_instance__
    #define ELROND_MOD_NEW_INST_FUNC_N __elrond_new_instance__
    #define ELROND_MOD_DEL_INST_FUNC_N __elrond_delete_instance__
    #define ELROND_MOD_API_VER_FUNC_N __elrond_api_ver__
    #define ELROND_MOD_MAIN_CLASS_FUNC_N __elrond_main_class_name__

    #define ELROND_MOD_PRETTY_NAME_FUNC_N __elrond_info_pretty_name__
    #define ELROND_MOD_AUTHOR_NAME_FUNC_N __elrond_info_author_name__
    #define ELROND_MOD_AUTHOR_EMAIL_FUNC_N __elrond_info_author_email__
    #define ELROND_MOD_VERSION_FUNC_N __elrond_info_version__

    #define ELROND_DEFINE_MODULE(C) ELROND_MOD_INFO_APP_P ELROND_MOD_APP_VAR = nullptr;\
                                    extern  "C" {void ELROND_MOD_SET_APP_FUNC_N (ELROND_MOD_INFO_APP_P a)\
                                                { ELROND_MOD_APP_VAR = a; }\
                                                ELROND_MOD_INFO_MOD_P ELROND_MOD_NEW_INST_FUNC_N ()\
                                                { return (ELROND_MOD_INFO_MOD_P) new C(); }\
                                                void ELROND_MOD_DEL_INST_FUNC_N (ELROND_MOD_INFO_MOD_P o)\
                                                { delete o; }\
                                                ELROND_MOD_INFO_NUM_T ELROND_MOD_API_VER_FUNC_N ()\
                                                { return elrond::makeDWord(ELROND_API_VERSION, ELROND_API_REVISION); }\
                                                ELROND_MOD_INFO_STR_T ELROND_MOD_MAIN_CLASS_FUNC_N ()\
                                                { return #C; }}

    #define ELROND_DEFINE_MODULE_PRETTY_NAME(N) extern "C" ELROND_MOD_INFO_STR_T ELROND_MOD_PRETTY_NAME_FUNC_N (){ return N; }
    #define ELROND_DEFINE_MODULE_AUTHOR_NAME(N) extern "C" ELROND_MOD_INFO_STR_T ELROND_MOD_AUTHOR_NAME_FUNC_N (){ return N; }
    #define ELROND_DEFINE_MODULE_AUTHOR_EMAIL(E) extern "C" ELROND_MOD_INFO_STR_T ELROND_MOD_AUTHOR_EMAIL_FUNC_N (){ return E; }
    #define ELROND_DEFINE_MODULE_VERSION(V) extern "C" ELROND_MOD_INFO_STR_T ELROND_MOD_VERSION_FUNC_N (){ return V; }

    #ifdef ELROND_WITH_MODULES_INFO
        #define ELROND_DEFINE_INTER_MOD_DEF_FUNCS static ELROND_MOD_INFO_STR_T ELROND_MOD_MAIN_CLASS_FUNC_N ();\
                                                  static ELROND_MOD_INFO_NUM_T ELROND_MOD_API_VER_FUNC_N ();\
                                                  static ELROND_MOD_INFO_STR_T ELROND_MOD_PRETTY_NAME_FUNC_N ();\
                                                  static ELROND_MOD_INFO_STR_T ELROND_MOD_AUTHOR_NAME_FUNC_N ();\
                                                  static ELROND_MOD_INFO_STR_T ELROND_MOD_AUTHOR_EMAIL_FUNC_N ();\
                                                  static ELROND_MOD_INFO_STR_T ELROND_MOD_VERSION_FUNC_N ();

        #define ELROND_DEFINE_INTER_MOD(C, P, A, E, V) ELROND_MOD_INFO_NUM_T C::ELROND_MOD_API_VER_FUNC_N ()\
                                                       { return elrond::makeDWord(ELROND_API_VERSION, ELROND_API_REVISION); }\
                                                       ELROND_MOD_INFO_STR_T C::ELROND_MOD_PRETTY_NAME_FUNC_N (){ return P; }\
                                                       ELROND_MOD_INFO_STR_T C::ELROND_MOD_AUTHOR_NAME_FUNC_N (){ return A; }\
                                                       ELROND_MOD_INFO_STR_T C::ELROND_MOD_AUTHOR_EMAIL_FUNC_N (){ return E; }\
                                                       ELROND_MOD_INFO_STR_T C::ELROND_MOD_VERSION_FUNC_N (){ return V; }\
                                                       ELROND_MOD_INFO_STR_T C::ELROND_MOD_MAIN_CLASS_FUNC_N ()\
                                                       { return #C; }

    #else
        #define ELROND_DEFINE_INTER_MOD_DEF_FUNCS
        #define ELROND_DEFINE_INTER_MOD(C, P, A, E, V) // C, P, A, E, V
    #endif

#endif
