#include "test/RuntimeTest.hpp"

#include <string>

using elrond::test::RuntimeTest;
using elrond::interface::Runtime;
using elrond::interface::Module;
using ConfigMapInterface = elrond::interface::ConfigMap;
using elrond::interface::DebugOut;
using elrond::module::BaseGpioModule;
using elrond::module::BaseInputDriverModule;
using elrond::channel::BaseChannelManager;

Runtime* elrond::__rtInstance__ = nullptr;

const RuntimeTest& RuntimeTest::init(Module& inst, ConfigMapInterface &cfg) const
{
    inst.onInit(cfg);
    return *this;
}

const RuntimeTest& RuntimeTest::start(Module& inst, std::function<bool()> loopContinue) const
{
    inst.onStart();

    elrond::timeT timeout = 0;
    const auto allow = inst.getLoopControl().allow;
    const auto loopTime = inst.getLoopControl().time;

    while(loopContinue()){
        if(allow){
            if(timeout >= elrond::millis()) continue;
            inst.loop();
            timeout = elrond::millis() + loopTime;
        }
    }

    inst.onStop();

    return *this;
}

BaseGpioModule& RuntimeTest::getGpioService() const
{
    if(this->gpio == nullptr) throw "Undefined Gpio service";
    return *(this->gpio);
}

BaseInputDriverModule& RuntimeTest::getInputService(const elrond::sizeT id) const
{
    if(this->input == nullptr) throw "Undefined Input service";
    return *(this->input);
}

BaseChannelManager& RuntimeTest::getChannelManager(const elrond::sizeT id) const
{
    if(this->chmgr == nullptr) throw "Undefined Chmgr service";
    return *(this->chmgr);
}

const DebugOut& RuntimeTest::dout() const
{
    if(this->debugOut == nullptr) throw "Undefined Debug service";
    return *(this->debugOut);
}

void RuntimeTest::onError(const char *error)
{
    throw std::string("Error: ") + error;
}

#ifdef ELROND_WITH_STR_TYPE
    void RuntimeTest::onError(elrond::String error)
    {
        throw std::string("Error: ") + error;
    }
#endif

RuntimeTest& RuntimeTest::set(BaseGpioModule& gpio)
{
    this->gpio = &gpio;
    return *this;
}

RuntimeTest& RuntimeTest::set(BaseInputDriverModule &input)
{
    this->input = &input;
    return *this;
}

RuntimeTest& RuntimeTest::set(BaseChannelManager &chmgr)
{
    this->chmgr = &chmgr;
    return *this;
}

RuntimeTest& RuntimeTest::set(DebugOut &dout)
{
    this->debugOut = &dout;
    return *this;
}

void RuntimeTest::setAppInstance(elrond::interface::Runtime* app)
{
    elrond::__rtInstance__ = app;
}
