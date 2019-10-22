#if !defined  _ELROND_BASE_GPIO_PIN_HPP
#define _ELROND_BASE_GPIO_PIN_HPP

    #include "types.hpp"

    namespace elrond {
        namespace gpio {

            class BaseGpioPin {

                protected:

                    int pin = -1;
                    elrond::gpio::gpioReadHandleT readHandle = nullptr;
                    elrond::gpio::gpioWriteHandleT writeHandle = nullptr;

                public:

                    virtual void attach(int pin);
                    virtual int getNumber() const;
                    virtual elrond::GpioType getType() const =0;

                    virtual elrond::word read();
                    virtual void write(elrond::word data);

                    virtual void setReadHandle(elrond::gpio::gpioReadHandleT handle);
                    virtual void setWriteHandle(elrond::gpio::gpioWriteHandleT handle);
            };
        }
    }

#endif
