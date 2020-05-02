#if !defined  _ELROND_BASE_GPIO_PIN_HPP
#define _ELROND_BASE_GPIO_PIN_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace gpio {

            class BaseGpioPin {

                protected:

                    int pin = -1;
                    elrond::gpio::ReadHandleT readHandle = nullptr;
                    elrond::gpio::WriteHandleT writeHandle = nullptr;

                public:

                    virtual void attach(int pin);
                    virtual int getNumber() const;
                    virtual elrond::GpioType getType() const =0;

                    virtual elrond::word read();
                    virtual void write(const elrond::word data);

                    virtual void setReadHandle(elrond::gpio::ReadHandleT handle);
                    virtual void setWriteHandle(elrond::gpio::WriteHandleT handle);
            };
        }
    }

#endif
