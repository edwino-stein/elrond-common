#if !defined  _ELROND_GPIO_PIN_HPP
#define _ELROND_GPIO_PIN_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace gpio {

            template<elrond::GpioType G>
            class GpioPin : public elrond::gpio::BaseGpioPin {
                public:
                    elrond::GpioType type() const override;
            };
        }
    }

#endif
