#if !defined  _ELROND_TEST_HPP
    #define _ELROND_TEST_HPP

    #include "elrond.hpp"

    #ifndef ELROND_WITH_LAMBDA_TYPE
        #error "The Elrond Test Library requires the ELROND_WITH_LAMBDA_TYPE macro"
    #endif

    #include "elrond-test/ConfigMap.hpp"
    #include "elrond-test/RuntimeTest.hpp"
    #include "elrond-test/ChannelManagerTest.hpp"
    #include "elrond-test/TransportTest.hpp"
    #include "elrond-test/InputDriverTest.hpp"
    #include "elrond-test/GpioTest.hpp"
    #include "elrond-test/DebugOut.hpp"

    #include "catch.hpp"

#endif
