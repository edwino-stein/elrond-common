#if !defined  _ELROND_TEST_TYPES_HPP
    #define _ELROND_TEST_TYPES_HPP

    #include "elrond_ext.hpp"

    #ifndef GENERIC_STD_PLATFORM
        #error "The Elrond Test Library requires the GENERIC_STD_PLATFORM macro"
    #endif

    #ifndef ELROND_WITH_LAMBDA_TYPE
        #error "The Elrond Test Library requires the ELROND_WITH_LAMBDA_TYPE macro"
    #endif

    #ifndef ELROND_WITH_STR_TYPE
        #error "The Elrond Test Library requires the ELROND_WITH_STR_TYPE macro"
    #endif

    #include <vector>
    #include <memory>
    #include <map>
    #include <sstream>

    namespace elrond {
        namespace test {
            class ConfigMapTest;
            class RuntimeTest;
            class RxChannelTest;
            class ChannelManagerTest;
            class TransportTest;
            class InputDriverTest;
            class GpioTest;
            class DebugOutTest;
            class ExternalModuleTest;
        }
    }

#endif
