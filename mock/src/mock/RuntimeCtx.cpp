#include "mock/RuntimeCtx.hpp"

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::interface::Context;
using elrond::platform::ModuleObject;
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
}

/* ************** elrond::platform::RuntimeCtx base overload ****************** */

Context const& RuntimeCtx::ofInstance(const ModuleObject& inst) const
{
    if(this->inst.get() == &inst) return *this;
    throw std::runtime_error("Invalid module context");
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
