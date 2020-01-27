#include "gpio/BaseGpioPin.hpp"
#include "interface/Runtime.hpp"
#include "module/BaseGpioModule.hpp"

/*  ****************************************************************************
    ***************** elrond::gpio::BaseGpioPin Implementation *****************
    ****************************************************************************/

namespace elrond {
    namespace gpio {

        ELROND_INLINE_FUNC void BaseGpioPin::attach(int pin)
        {
            this->pin = pin;
            elrond::app().getGpioService().attach(*this);
        }

        ELROND_INLINE_FUNC int BaseGpioPin::getNumber() const
        { return this->pin; }

        ELROND_INLINE_FUNC elrond::word BaseGpioPin::read()
        { return this->readHandle != nullptr ? this->readHandle(*this) : 0; }

        ELROND_INLINE_FUNC void BaseGpioPin::write(const elrond::word data)
        { if(this->writeHandle != nullptr) this->writeHandle(*this, data); }

        ELROND_INLINE_FUNC void BaseGpioPin::setReadHandle(elrond::gpio::ReadHandleT handle)
        { this->readHandle = handle; }

        ELROND_INLINE_FUNC void BaseGpioPin::setWriteHandle(elrond::gpio::WriteHandleT handle)
        { this->writeHandle = handle; }
    }
}
