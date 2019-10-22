#if !defined  _ELROND_GENERIC_GPIO_PIN_HPP
#define _ELROND_GENERIC_GPIO_PIN_HPP

    #include "types.hpp"
    #include "runtime/gpio/BaseGpioPin.hpp"

    namespace elrond {
        namespace gpio {

            template<class T, elrond::GpioType G>
            class GenericGpioPin : public elrond::gpio::BaseGpioPin {
                public:
                    T value;
                    virtual elrond::GpioType getType() const override;
            };

            template<class T, elrond::GpioType G>
            elrond::GpioType GenericGpioPin<T, G>::getType() const {
                return G;
            }
        }
    }

#endif
