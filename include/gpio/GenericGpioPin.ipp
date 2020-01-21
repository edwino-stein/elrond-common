#if !defined  _ELROND_GENERIC_GPIO_PIN_IPP
#define _ELROND_GENERIC_GPIO_PIN_IPP

    #include "types.hpp"
    #include "gpio/BaseGpioPin.hpp"

    namespace elrond {
        namespace gpio {

            /* ****************************************************************
               ********* elrond::gpio::GenericGpioPin Implementation **********
               **************************************************************** */

            template<class T, elrond::GpioType G>
            elrond::GpioType GenericGpioPin<T, G>::getType() const {
                return G;
            }
        }
    }

#endif
