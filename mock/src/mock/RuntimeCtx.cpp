#include "mock/RuntimeCtx.hpp"
#include "mock/Console.hpp"

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::interface::Context;
using elrond::platform::ModuleObject;
using elrond::interface::Console;

using PlatfomCtx = elrond::platform::RuntimeCtx;

/*  ****************************************************************************
    ***************** elrond::mock::RuntimeCtx Implementation ******************
    ****************************************************************************/

/* ******************************* Constructors ******************************* */

RuntimeCtx::RuntimeCtx(elrond::string name, Module* const inst)
:
    name(name),
    inst(inst),
    consoleInst(nullptr)
{
    this->inst->__init__(this);
    this->console(elrond::mock::Console::null());
}

/* ************** elrond::platform::RuntimeCtx base overload ****************** */

Context const& RuntimeCtx::ofInstance(const ModuleObject& inst) const
{
    if(this->inst.get() == &inst) return *this;
    throw std::runtime_error("Invalid module context");
}

/* *************** elrond::interface::Context base overload ******************* */

Console const& RuntimeCtx::console() const
{
    return *(this->consoleInst);
}

/* *********************************** Setters ******************************** */

RuntimeCtx& RuntimeCtx::console(elrond::interface::Console& console)
{
    this->consoleInst = &console;
    return *this;
}

/* *********************************** Others ********************************* */

//
// Module lifecycle
//

RuntimeCtx& RuntimeCtx::callSetup()
{
    this->inst->setup();
    return *this;
}

RuntimeCtx& RuntimeCtx::callStart()
{
    this->inst->start();
    return *this;
}

RuntimeCtx& RuntimeCtx::callLoop()
{
    return this->callLoop(1);
}

RuntimeCtx& RuntimeCtx::callLoop(const elrond::sizeT times)
{
    elrond::sizeT count = 0;
    return this->callLoop([&count, &times](){ return count++ < times; });
}

RuntimeCtx& RuntimeCtx::callLoop(elrond::function<bool> predic)
{
    while (predic()) this->inst->loop();
    return *this;
}

RuntimeCtx& RuntimeCtx::callStop()
{
    this->inst->stop();
    return *this;
}
