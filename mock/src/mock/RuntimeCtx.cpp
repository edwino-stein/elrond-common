#include "mock/RuntimeCtx.hpp"

#include "mock/ConsoleAdapter.hpp"
#include "mock/Arguments.hpp"

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::platform::ModuleObject;
using elrond::interface::Console;
using elrond::mock::Arguments;
using elrond::mock::ConsoleAdapter;
using elrond::platform::BaseFactoryAdapter;
using elrond::platform::FactoryAdapterP;
using elrond::platform::ExternalFactoryAdapter;
using elrond::platform::ModuleInfo;

using ContextInterface = elrond::interface::Context;
using PlatfomCtx = elrond::platform::RuntimeCtx;

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

/*  ****************************************************************************
    ***************** elrond::mock::RuntimeCtx Implementation ******************
    ****************************************************************************/

const ModuleInfo RuntimeCtx::mockedModuleInfo;

/* ******************************* Constructors ******************************* */

RuntimeCtx::RuntimeCtx(elrond::string name, FactoryAdapterP adapter)
:
    _adapter(adapter),
    _instance(_adapter->create(name)),
    _consoleAdapter(ConsoleAdapter::null()),
    _arguments(Arguments::null())
{
    this->instance().__init__(this);
}

/* ************** elrond::platform::RuntimeCtx base overload ****************** */

elrond::pointer<ContextInterface> RuntimeCtx::ofInstance(const ModuleObject& inst) const
{
    if(&(this->instance()) != &inst) throw std::runtime_error("Invalid module context");
    return std::make_shared<RuntimeCtx::Context>(*this);
}

/* *********************************** Setters ******************************** */

RuntimeCtx& RuntimeCtx::console(elrond::interface::ConsoleAdapter& consoleAdapter)
{
    this->_consoleAdapter = &consoleAdapter;
    return *this;
}

RuntimeCtx& RuntimeCtx::arguments(elrond::mock::Arguments& args)
{
    this->_arguments = &args;
    return *this;
}

/* *********************************** Getters ******************************** */

elrond::pointer<Console> RuntimeCtx::console() const
{
    return std::make_shared<elrond::runtime::Console>(
        this->name(),
        *(this->_consoleAdapter)
    );
}

elrond::pointer<elrond::interface::Arguments>
RuntimeCtx::arguments() const
{
    return std::make_shared<Arguments>(*(this->_arguments));
}

elrond::string RuntimeCtx::name() const
{
    return this->_instance->name();
}

elrond::interface::Module& RuntimeCtx::instance() const
{
    return this->_instance->instance();
}

BaseFactoryAdapter& RuntimeCtx::adapter() const
{
    return *(this->_adapter);
}

/* *********************************** Others ********************************* */

//
// Module lifecycle
//

RuntimeCtx& RuntimeCtx::callSetup()
{
    this->instance().setup(*(this->arguments()));
    return *this;
}

RuntimeCtx& RuntimeCtx::callStart()
{
    this->instance().start();
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
    while (predic()) this->instance().loop();
    return *this;
}

RuntimeCtx& RuntimeCtx::callStop()
{
    this->instance().stop();
    return *this;
}

/* *********************************** Static ********************************* */

RuntimeCtx RuntimeCtx::create(elrond::string name, elrond::string path)
{
    return RuntimeCtx(name, std::make_shared<ExternalFactoryAdapter>(path));
}
