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
            class TxChannelTest;
            class ChannelManagerTest;
            class DataLinkTest;
            class InputDriverTest;
            class InputListenerTest;
            class InputTriggerTest;
            class GpioTest;
            template <elrond::GpioType G> class GpioPinTest;
            class DebugOutTest;
            class ExternalModuleTest;

            // GPIO types
            using DOutPinTest = GpioPinTest<elrond::GpioType::DOUT>;
            using DInPDPinTest = GpioPinTest<elrond::GpioType::DIN_PD>;
            using DInPUPinTest = GpioPinTest<elrond::GpioType::DIN_PU>;
            using AInPinTest = GpioPinTest<elrond::GpioType::AIN>;
            using ServoPinTest = GpioPinTest<elrond::GpioType::SERVO>;
            using PwmPinTest = GpioPinTest<elrond::GpioType::PWM>;

            template<typename B, typename T>
            inline bool baseOf(const T*) { return std::is_base_of<B, T>::value; }

            template<class T, typename B>
            inline bool instanceOf(B const* o) { return dynamic_cast<T const*>(o) != nullptr; }
        }

    }

#endif
