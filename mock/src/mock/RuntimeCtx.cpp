#include "mock/RuntimeCtx.hpp"

#include "mock/ConsoleAdapter.hpp"
#include "mock/Arguments.hpp"
#include "mock/ModuleInstanceHandle.hpp"

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::interface::Console;
using elrond::mock::Arguments;
using elrond::mock::ConsoleAdapter;
using elrond::interface::Factory;
using elrond::mock::ModuleInstanceHandle;
using elrond::mock::ExternalInstanceModuleHandle;

using IConsoleAdapter = elrond::interface::ConsoleAdapter;
using IArguments = elrond::interface::Arguments;

/*  ****************************************************************************
    ************ elrond::mock::RuntimeCtx::Context Implementation **************
    ****************************************************************************/

RuntimeCtx::Context::Context(const RuntimeCtx& ctx) : ctx(ctx) {}

elrond::pointer<Console> RuntimeCtx::Context::console() const
{
    return this->ctx.console();
}

elrond::pointer<elrond::interface::Arguments>
RuntimeCtx::Context::arguments() const
{
    return this->ctx.arguments();
}

elrond::string RuntimeCtx::Context::name() const
{
    return this->ctx.name();
}

void RuntimeCtx::Context::loopEnable(bool enable)
{
    const_cast<RuntimeCtx&>(this->ctx)._loopEnable = enable;
}

void RuntimeCtx::Context::loopInterval(elrond::timeT interval)
{
    const_cast<RuntimeCtx&>(this->ctx)._loopInterval = interval;
}

void RuntimeCtx::Context::loopAsync(bool enable)
{
    const_cast<RuntimeCtx&>(this->ctx)._loopAsync = enable;
}

/*  ****************************************************************************
    ***************** elrond::mock::RuntimeCtx Implementation ******************
    ****************************************************************************/

/* ******************************* Constructors ******************************* */

RuntimeCtx::RuntimeCtx(std::shared_ptr<ModuleInstanceHandle> moduleHandle)
:
    _moduleHandle(moduleHandle),
    _consoleAdapter(ConsoleAdapter::null()),
    _arguments(Arguments::null()),
    _loopEnable(false),
    _loopAsync(false),
    _loopInterval(0)
{}

/* *********************************** Setters ******************************** */

RuntimeCtx& RuntimeCtx::console(IConsoleAdapter& consoleAdapter)
{
    this->_consoleAdapter = &consoleAdapter;
    return *this;
}

RuntimeCtx& RuntimeCtx::arguments(Arguments& args)
{
    this->_arguments = &args;
    return *this;
}

/* *********************************** Getters ******************************** */

elrond::ContextP RuntimeCtx::ctx() const
{
    return std::make_shared<RuntimeCtx::Context>(*this);
}

elrond::pointer<Console> RuntimeCtx::console() const
{
    return std::make_shared<elrond::runtime::Console>(*(this->_consoleAdapter));
}

elrond::pointer<IArguments> RuntimeCtx::arguments() const
{
    return std::make_shared<Arguments>(*(this->_arguments));
}

elrond::string RuntimeCtx::name() const
{
    return this->_moduleHandle->name();
}

Module& RuntimeCtx::instance() const
{
    return this->_moduleHandle->instance();
}

Factory& RuntimeCtx::factory() const
{
    return this->_moduleHandle->factory();
}

bool RuntimeCtx::loopEnable() const
{
    return this->_loopEnable;
}

elrond::timeT RuntimeCtx::loopInterval() const
{
    return this->_loopInterval;
}

bool RuntimeCtx::loopAsync() const
{
    return this->_loopAsync;
}

/* *********************************** Others ********************************* */

//
// Module lifecycle
//

RuntimeCtx& RuntimeCtx::callSetup()
{
    this->instance().setup(this->ctx());
    return *this;
}

RuntimeCtx& RuntimeCtx::callStart()
{
    this->instance().start(this->ctx());
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
    while (predic()) this->instance().loop(this->ctx());
    return *this;
}

RuntimeCtx& RuntimeCtx::callStop()
{
    this->instance().stop(this->ctx());
    return *this;
}

/* *********************************** Static ********************************* */

RuntimeCtx RuntimeCtx::create(const elrond::string& name, const elrond::string& path)
{
    auto adapter = std::make_shared<ExternalInstanceModuleHandle>(name, path);
    return RuntimeCtx(adapter);
}
