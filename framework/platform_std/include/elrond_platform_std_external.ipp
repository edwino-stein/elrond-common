#ifndef ELROND_PLATFORM_STD_EXTERNAL_IPP
    #define ELROND_PLATFORM_STD_EXTERNAL_IPP

    #ifndef ELROND_ENABLE_EXTERNAL_ABI_SETUP
        #error "This header must be used with ELROND_ENABLE_EXTERNAL_ABI_SETUP macro"
    #endif

    #include "elrond_common_types.hpp"

    #define ELROND_DEFINE_DEFAULT_MODULE(C, ...) \
        extern "C" { \
            ELROND_ABI_EXPORT ELROND_ABI_NUM_TYPE ELROND_ABI_GET_API_VERSION_FUNC_NAME () \
            { return elrond::getApiVersion(); } \
            ELROND_ABI_EXPORT ELROND_ABI_FACTORY_TYPE ELROND_ABI_GET_FACTORY_FUNC_NAME () {\
                static elrond::platform::Factory<C> moduleFactory({__VA_ARGS__}); \
                return &moduleFactory; \
            } \
        }

#endif
