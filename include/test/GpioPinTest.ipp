#if !defined  _ELROND_GPIO_PIN_TEST_IPP
#define _ELROND_GPIO_PIN_TEST_IPP

    #include "test/GpioPinTest.hpp"

    namespace elrond {
        namespace test {

            /* *****************************************************************
               ************ elrond::test::GpioPinTest Implementation ***********
               ***************************************************************** */

            template<elrond::GpioType G>
            GpioPinTest<G>::GpioPinTest(
                const elrond::uInt8 pin,
                elrond::module::BaseGpioModule& gpio
            ){
                this->_pin = pin;
                this->gpio = &(gpio);
                this->gpio->attach(*this);
            }
        }
    }

#endif
