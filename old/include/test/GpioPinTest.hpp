#if !defined  _ELROND_GPIO_PIN_TEST_HPP
#define _ELROND_GPIO_PIN_TEST_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            template<elrond::GpioType G>
            class GpioPinTest : public elrond::gpio::GpioPin<G> {
                public:
                    GpioPinTest(const elrond::uInt8 pin, elrond::module::BaseGpioModule& gpio);
                    void attach(elrond::uInt8 pin) = delete;
            };
        }
    }

#endif
