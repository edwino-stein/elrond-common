#include "elrond-test/GpioTest.hpp"

using elrond::test::GpioTest;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;
using elrond::gpio::AInPin;
using elrond::gpio::ServoPin;
using elrond::gpio::PwmPin;
using elrond::gpio::WriteHandleT;
using elrond::gpio::ReadHandleT;

GpioTest::GpioTest(WriteHandleT onWrite, ReadHandleT onRead)
{
    GpioTest &me = *this;

    if(onWrite == nullptr){
        this->onWrite = [&me](BaseGpioPin& pin, const elrond::word data)
        {
            switch (pin.getType()) {
                case elrond::GpioType::DOUT: me.write((DOutPin&) pin, data); break;
                case elrond::GpioType::PWM: me.write((PwmPin&) pin, data); break;
                case elrond::GpioType::SERVO: me.write((ServoPin&) pin, data); break;
                default: return;
            }
        };
    }
    else {
        this->onWrite = onWrite;
    }

    if(onRead == nullptr){
        this->onRead = [&me](BaseGpioPin& pin)
        {
            switch (pin.getType()) {
                case elrond::GpioType::DOUT: return me.read((DOutPin&) pin); break;
                case elrond::GpioType::PWM: return me.read((PwmPin&) pin); break;
                case elrond::GpioType::SERVO: return me.read((ServoPin&) pin); break;
                case elrond::GpioType::AIN: return me.read((AInPin&) pin); break;
                default: return (elrond::word) 0;
            }
        };

    }
    else {
        this->onRead = onRead;
    }
}

void GpioTest::attach(BaseGpioPin &pin)
{
    if(pin.getType() == elrond::GpioType::UNKNOWN) throw "Invalid GPIO pin type";
    pin.setWriteHandle(this->onWrite);
    pin.setReadHandle(this->onRead);
}

DOutPin& GpioTest::attachDOut(int pin)
{
    GpioTest::BaseGpioPinP bp(new GpioTest::TestDOutPin(pin));
    DOutPin& p = *((DOutPin*) bp.get());
    this->attach(p);
    this->testPinInsts.push_back(std::move(bp));
    return p;
}

AInPin& GpioTest::attachAIn(int pin)
{
    GpioTest::BaseGpioPinP bp(new GpioTest::TestAInPin(pin));
    AInPin& p = *((AInPin*) bp.get());
    this->attach(p);
    this->testPinInsts.push_back(std::move(bp));
    return p;
}

PwmPin& GpioTest::attachPwm(int pin)
{
    GpioTest::BaseGpioPinP bp(new GpioTest::TestPwmPin(pin));
    PwmPin& p = *((PwmPin*) bp.get());
    this->attach(p);
    this->testPinInsts.push_back(std::move(bp));
    return p;
}

ServoPin& GpioTest::attachServo(int pin)
{
    GpioTest::BaseGpioPinP bp(new GpioTest::TestServoPin(pin));
    ServoPin& p = *((ServoPin*) bp.get());
    this->attach(p);
    this->testPinInsts.push_back(std::move(bp));
    return p;
}

void GpioTest::write(DOutPin& pin, const elrond::word data) const {
    pin.value = data > 0 ? HIGH_VALUE : LOW_VALUE;
}

void GpioTest::write(PwmPin& pin, const elrond::word data) const {
    pin.value = data;
}

void GpioTest::write(ServoPin& pin, const elrond::word data) const {
    pin.value = elrond::map(
        data,
        LOW_VALUE,
        HIGH_VALUE,
        0,
        180
    );
}

elrond::word GpioTest::read(DOutPin& pin) const { return pin.value; }
elrond::word GpioTest::read(PwmPin& pin) const { return pin.value; }
elrond::word GpioTest::read(ServoPin& pin) const { return pin.value; }
elrond::word GpioTest::read(AInPin& pin) const
{
    auto it = this->testAinValues.find(pin.getNumber());
    if(it != this->testAinValues.end()) pin.value = it->second;
    return pin.value;
}

void GpioTest::simulateAin(const int pin, const elrond::word data)
{
    auto it = this->testAinValues.find(pin);
    if(it != this->testAinValues.end()) this->testAinValues.erase(it);
    this->testAinValues[pin] = data;
}

GpioTest::TestDOutPin::TestDOutPin(int pin) { this->pin = pin; }
GpioTest::TestPwmPin::TestPwmPin(int pin) { this->pin = pin; }
GpioTest::TestServoPin::TestServoPin(int pin) { this->pin = pin; }
GpioTest::TestAInPin::TestAInPin(int pin) { this->pin = pin; }
