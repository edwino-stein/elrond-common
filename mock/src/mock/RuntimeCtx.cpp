#include "mock/RuntimeCtx.hpp"
#include "mock/ModuleInstanceHandle.hpp"

using elrond::mock::RuntimeCtx;
using elrond::mock::Context;
using elrond::mock::Application;
using elrond::interface::Module;
using elrond::interface::Factory;
using elrond::mock::ModuleInstanceHandle;
using elrond::mock::ExternalInstanceModuleHandle;
using IContext = elrond::interface::Context;
using IConsole = elrond::interface::Console;
using IArguments = elrond::interface::Arguments;

/*  ****************************************************************************
    ***************** elrond::mock::RuntimeCtx Implementation ******************
    ****************************************************************************/

/* ******************************* Constructors ******************************* */

RuntimeCtx::RuntimeCtx(std::shared_ptr<ModuleInstanceHandle> moduleHandle)
: Application(), _moduleHandle(moduleHandle) {}

/* *********************************** Getters ******************************** */

ModuleInstanceHandle& RuntimeCtx::moduleHandle() const
{
    return *(this->_moduleHandle);
}

Module& RuntimeCtx::instance() const
{
    return this->_moduleHandle->instance();
}

Factory& RuntimeCtx::factory() const
{
    return this->_moduleHandle->factory();
}

/* *********************************** Others ********************************* */

elrond::pointer<IContext> RuntimeCtx::makeCtx()
{
    return std::make_shared<Context>(*this);
}

//
// Module lifecycle
//

RuntimeCtx& RuntimeCtx::callSetup()
{
    this->instance().setup(this->makeCtx());
    return *this;
}

RuntimeCtx& RuntimeCtx::callStart()
{
    this->instance().start(this->makeCtx());
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
    while (predic()) this->instance().loop(this->makeCtx());
    return *this;
}

RuntimeCtx& RuntimeCtx::callStop()
{
    this->instance().stop(this->makeCtx());
    return *this;
}

/* *********************************** Static ********************************* */

RuntimeCtx RuntimeCtx::create(const elrond::string& name, const elrond::string& path)
{
    auto adapter = std::make_shared<ExternalInstanceModuleHandle>(name, path);
    return RuntimeCtx(adapter);
}


/*  ****************************************************************************
    ***************** elrond::mock::Context Implementation *********************
    ****************************************************************************/

Context::Context(RuntimeCtx& app) : _app(&app) {}

elrond::pointer<IConsole> Context::console() const
{ return this->_app->makeConsole(); }

elrond::pointer<IArguments> Context::arguments() const
{ return this->_app->makeArguments(); }

elrond::string Context::name() const
{ return this->_app->moduleHandle().name(); }

void Context::setLoopEvery(const elrond::TimeSpan& ts)
{
    this->_app->moduleHandle().loopEnable = true;
    this->_app->moduleHandle().loopTs = ts;
}

void Context::unsetLoop()
{
    this->_app->moduleHandle().loopEnable = false;
    this->_app->moduleHandle().loopTs = elrond::seconds(0);
}
