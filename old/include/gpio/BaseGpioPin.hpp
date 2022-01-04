#if !defined  _ELROND_BASE_GPIO_PIN_HPP
#define _ELROND_BASE_GPIO_PIN_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace gpio {

            class BaseGpioPin {

                protected:
                    elrond::uInt8 _pin;
                    elrond::module::BaseGpioModule* gpio = nullptr;

                public:

                    elrond::uInt16 pin() const;
                    void attach(elrond::uInt8 pin);
                    elrond::word read();
                    void write(const elrond::word data);

                    virtual elrond::GpioType type() const =0;
            };
        }
    }

#endif
