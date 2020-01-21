#include "gpio/BaseGpioPin.hpp"
#include "interface/Runtime.hpp"
#include "module/BaseGpioModule.hpp"

using elrond::gpio::BaseGpioPin;
using elrond::interface::Runtime;
using elrond::module::BaseGpioModule;

/*  ****************************************************************************
    ***************** elrond::gpio::BaseGpioPin Implementation *****************
    ****************************************************************************/

void BaseGpioPin::attach(int pin)
{
    this->pin = pin;
    elrond::app().getGpioService().attach(*this);
}

int BaseGpioPin::getNumber() const
{
    return this->pin;
}

elrond::word BaseGpioPin::read()
{
    return this->readHandle != nullptr ? this->readHandle(*this) : 0;
}

void BaseGpioPin::write(const elrond::word data)
{
    if(this->writeHandle != nullptr) this->writeHandle(*this, data);
}

void BaseGpioPin::setReadHandle(elrond::gpio::ReadHandleT handle)
{
    this->readHandle = handle;
}

void BaseGpioPin::setWriteHandle(elrond::gpio::WriteHandleT handle)
{
    this->writeHandle = handle;
}
