#include "test/GpioTest.hpp"

using elrond::test::GpioTest;
using elrond::gpio::BaseGpioPin;

GpioTest::GpioTest(OnAttachT onAttach, OnWriteT onWrite)
{
    if(onAttach != nullptr) this->onAttach = onAttach;
    if(onWrite != nullptr) this->onWrite = onWrite;
}


void GpioTest::attach(BaseGpioPin& pin)
{
    auto it = this->pinHeader.find(pin.pin());
    if(it != this->pinHeader.end()) return;
    this->pinHeader[pin.pin()] = 0;
    if(this->onAttach != nullptr) this->onAttach(pin);
}

elrond::word GpioTest::read(BaseGpioPin& pin)
{
    auto it = this->pinHeader.find(pin.pin());
    const elrond::word data = it != this->pinHeader.end() ? it->second : 0;

    switch (pin.type()) {
        case elrond::GpioType::DOUT:
        case elrond::GpioType::DIN_PD:
            return data > 0 ? elrond::high : elrond::low;
        break;

        case elrond::GpioType::DIN_PU:
            return data > 0 ? elrond::low : elrond::high;
        break;

        case elrond::GpioType::AIN:
        case elrond::GpioType::PWM:
        case elrond::GpioType::SERVO:
        default:
            return data;
        break;
    }
}

void GpioTest::write(BaseGpioPin& pin, const elrond::word data)
{
    auto it = this->pinHeader.find(pin.pin());
    if(it == this->pinHeader.end()) return;

    switch (pin.type()) {
        case elrond::GpioType::DOUT:
            it->second = data > 0 ? elrond::high : elrond::low;
        break;

        case elrond::GpioType::PWM:
        case elrond::GpioType::SERVO:
            it->second = data;
        break;

        default:
            return;
    }

    if(this->onWrite != nullptr) this->onWrite(pin, it->second);
}

bool GpioTest::simulateInput(BaseGpioPin& pin, const elrond::word data)
{
    switch (pin.type()) {

        case elrond::GpioType::DOUT:
        case elrond::GpioType::PWM:
        case elrond::GpioType::SERVO:
            return false;
        break;

        default:
            auto it = this->pinHeader.find(pin.pin());
            if(it == this->pinHeader.end()) return false;
            it->second = data;
            return true;
    }
}
