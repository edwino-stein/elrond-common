#include "gpio/BaseGpioPin.hpp"
#include "interface/Runtime.hpp"
#include "module/BaseGpioModule.hpp"

/*  ****************************************************************************
    ***************** elrond::gpio::BaseGpioPin Implementation *****************
    ****************************************************************************/

namespace elrond {
    namespace gpio {

        ELROND_INLINE_FUNC elrond::uInt16 BaseGpioPin::pin() const
        { return this->_pin; }

        ELROND_INLINE_FUNC void BaseGpioPin::attach(const elrond::uInt8 pin)
        {
            if(this->gpio != nullptr) return;
            this->_pin = pin;
            this->gpio = &(elrond::app().getGpio());
            this->gpio->attach(*this);
        }

        ELROND_INLINE_FUNC elrond::word BaseGpioPin::read()
        { return this->gpio != nullptr ? this->gpio->read(*this) : 0; }

        ELROND_INLINE_FUNC void BaseGpioPin::write(const elrond::word data)
        { if(this->gpio != nullptr) this->gpio->write(*this, data); }
    }
}
