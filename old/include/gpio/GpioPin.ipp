#if !defined  _ELROND_GPIO_PIN_IPP
#define _ELROND_GPIO_PIN_IPP

    #include "gpio/GpioPin.hpp"

    namespace elrond {
        namespace gpio {

            /* *****************************************************************
               ************* elrond::gpio::GpioPin Implementation **************
               ***************************************************************** */

            template<elrond::GpioType G>
            elrond::GpioType GpioPin<G>::type() const { return G; }
        }
    }

#endif
