#include "test/RuntimeTest.hpp"

#include <string>

using elrond::test::RuntimeTest;
using elrond::interfaces::RuntimeInterface;
using elrond::interfaces::ModuleInterface;
using elrond::interfaces::ConfigMapInterface;
using elrond::interfaces::DebugOutInterface;
using elrond::modules::BaseGpioModule;
using elrond::modules::BaseInputDriverModule;
using elrond::channel::BaseChannelManager;

RuntimeInterface* elrond::__rtInstance__ = nullptr;

const RuntimeTest& RuntimeTest::init(ModuleInterface& inst, ConfigMapInterface &cfg) const
{
    inst.onInit(cfg);
    return *this;
}

const RuntimeTest& RuntimeTest::start(ModuleInterface& inst, std::function<bool()> loopContinue) const
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

const DebugOutInterface& RuntimeTest::dout() const
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

RuntimeTest& RuntimeTest::set(DebugOutInterface &dout)
{
    this->debugOut = &dout;
    return *this;
}

void RuntimeTest::setAppInstance(elrond::interfaces::RuntimeInterface* app)
{
    elrond::__rtInstance__ = app;
}
