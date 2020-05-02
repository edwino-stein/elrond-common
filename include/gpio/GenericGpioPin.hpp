#if !defined  _ELROND_GENERIC_GPIO_PIN_HPP
#define _ELROND_GENERIC_GPIO_PIN_HPP

    #include "elrond_types.hpp"
    #include "gpio/BaseGpioPin.hpp"

    namespace elrond {
        namespace gpio {

            template<class T, elrond::GpioType G>
            class GenericGpioPin : public elrond::gpio::BaseGpioPin {
                public:
                    T value;
                    virtual elrond::GpioType getType() const override;
            };
        }
    }

#endif
