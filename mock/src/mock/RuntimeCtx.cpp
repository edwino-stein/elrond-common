#include "mock/RuntimeCtx.hpp"

#include "mock/Console.hpp"
#include "mock/Parameters.hpp"

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::interface::Context;
using elrond::platform::ModuleObject;
using elrond::interface::Console;
using elrond::mock::Parameters;
using elrond::platform::BaseFactoryAdapter;
using elrond::platform::FactoryAdapterP;
using elrond::platform::ExternalFactoryAdapter;
using elrond::platform::ModuleInfo;

using PlatfomCtx = elrond::platform::RuntimeCtx;

/*  ****************************************************************************
    ***************** elrond::mock::RuntimeCtx Implementation ******************
    ****************************************************************************/

const ModuleInfo RuntimeCtx::mockedModuleInfo;

/* ******************************* Constructors ******************************* */

RuntimeCtx::RuntimeCtx(elrond::string name, FactoryAdapterP adapter)
:
    _adapter(adapter),
    _instance(_adapter->create(name)),
    _console(nullptr)
{
    this->instance().__init__(this);
    this->console(elrond::mock::Console::null());
}

/* ************** elrond::platform::RuntimeCtx base overload ****************** */

Context const& RuntimeCtx::ofInstance(const ModuleObject& inst) const
{
    if(&(this->instance()) == &inst) return *this;
    throw std::runtime_error("Invalid module context");
}

/* *************** elrond::interface::Context base overload ******************* */

Console const& RuntimeCtx::console() const
{
    return *(this->_console);
}

/* *********************************** Setters ******************************** */

RuntimeCtx& RuntimeCtx::console(elrond::interface::Console& console)
{
    this->_console = &console;
    return *this;
}

/* *********************************** Getters ******************************** */

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
    Parameters params;
    return this->callSetup(params);
}

RuntimeCtx& RuntimeCtx::callSetup(const elrond::Parameters& params)
{
    this->instance().setup(params);
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
