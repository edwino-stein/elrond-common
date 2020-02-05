#if !defined  _ELROND_TEST_HPP
    #define _ELROND_TEST_HPP

    #include "elrond.hpp"

    #ifndef GENERIC_STD_PLATFORM
        #error "The Elrond Test Library requires the GENERIC_STD_PLATFORM macro"
    #endif

    #ifndef ELROND_WITH_LAMBDA_TYPE
        #error "The Elrond Test Library requires the ELROND_WITH_LAMBDA_TYPE macro"
    #endif

    #include "test/ConfigMap.hpp"
    #include "test/RuntimeTest.hpp"
    #include "test/ExternalModuleTest.hpp"
    #include "test/ChannelManagerTest.hpp"
    #include "test/TransportTest.hpp"
    #include "test/InputDriverTest.hpp"
    #include "test/GpioTest.hpp"
    #include "test/DebugOut.hpp"

#endif
