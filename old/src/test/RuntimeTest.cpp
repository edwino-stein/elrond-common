#include "test/RuntimeTest.hpp"

using elrond::test::RuntimeTest;

using elrond::interface::Runtime;
using elrond::interface::Module;
using elrond::interface::ConfigMap;
using elrond::interface::Console;
using elrond::test::ConsoleTest;
using elrond::module::BaseGpioModule;
using elrond::module::BaseInputModule;
using elrond::interface::ChannelManager;
using elrond::channel::BaseChannelManager;
using elrond::LoopControl;

ConsoleTest RuntimeTest::builtInConsole;

RuntimeTest::RuntimeTest(const bool defaultApp)
{
    if(defaultApp) RuntimeTest::setAppInstance(this);
    this->set(RuntimeTest::getBuiltInConsole());
}

RuntimeTest::~RuntimeTest()
{ if(ELROND_MOD_APP_VAR == this) RuntimeTest::setAppInstance(nullptr); }

const RuntimeTest& RuntimeTest::init(Module& inst, ConfigMap &cfg, LoopControl &lc) const
{
    inst.onInit(cfg, lc);
    return *this;
}

const RuntimeTest& RuntimeTest::start(Module& inst, LoopControl& lc, std::function<bool()> loopContinue) const
{
    inst.onStart();

    elrond::timeT timeout = 0;
    const auto enable = lc.enable;
    const auto interval = lc.interval;

    while(loopContinue()){

        if(enable){
            if(timeout >= elrond::millis()) continue;
            inst.loop();
            timeout = elrond::millis() + interval;
        }

        if(this->chmgr != nullptr && this->autoSync) this->chmgr->txSync(true);
    }

    inst.onStop();

    return *this;
}

BaseGpioModule& RuntimeTest::getGpio() const
{
    if(this->gpio == nullptr) throw "Undefined Gpio module";
    return *(this->gpio);
}

BaseInputModule& RuntimeTest::getInput(const elrond::sizeT id) const
{
    if(this->input == nullptr) throw "Undefined Input module";
    return *(this->input);
}

ChannelManager& RuntimeTest::getChannelManager(const elrond::sizeT id) const
{
    if(this->chmgr == nullptr) throw "Undefined Channel Manager";
    return *((ChannelManager*) this->chmgr);
}

const Console& RuntimeTest::getInfoConsole() const
{
    if(this->console == nullptr) throw "Undefined Console";
    return *(this->console);
}

void RuntimeTest::onError(const char *error)
{ throw std::string("Error: ") + error; }

#ifdef ELROND_WITH_STR_TYPE
void RuntimeTest::onError(elrond::String error)
{ throw std::string("Error: ") + error; }
#endif

RuntimeTest& RuntimeTest::set(BaseGpioModule& gpio)
{
    this->gpio = &gpio;
    return *this;
}

RuntimeTest& RuntimeTest::set(BaseInputModule& input)
{
    this->input = &input;
    return *this;
}

RuntimeTest& RuntimeTest::set(BaseChannelManager& chmgr, const bool autoSync)
{
    this->chmgr = &chmgr;
    this->autoSync = autoSync;
    return *this;
}

RuntimeTest& RuntimeTest::set(Console& console)
{
    this->console = &console;
    return *this;
}

void RuntimeTest::setAppInstance(Runtime& app) { ELROND_MOD_APP_VAR = &app; }
void RuntimeTest::setAppInstance(Runtime* app) { ELROND_MOD_APP_VAR = app; }
ConsoleTest& RuntimeTest::getBuiltInConsole() { return RuntimeTest::builtInConsole; }
