#include "mock/Application.hpp"

#include "mock/ConsoleAdapter.hpp"
#include "mock/Arguments.hpp"

using elrond::mock::Application;
using elrond::mock::ConsoleAdapter;
using elrond::mock::ConsoleStreamAdapter;
using elrond::mock::Arguments;
using elrond::runtime::Console;
using IConsoleStreamAdapter = elrond::interface::ConsoleStreamAdapter;
using IArguments = elrond::interface::Arguments;
using IConsole = elrond::interface::Console;

Application::Application() :
    _consoleAdapter(&(ConsoleAdapter::null())),
    _arguments(Arguments::null())
{}

elrond::pointer<IConsole> Application::makeConsole() const
{ return std::make_shared<Console>(this->_consoleAdapter->makeConsoleStreamAdapter()); }

elrond::pointer<IArguments> Application::makeArguments() const
{ return std::wrap_shared<IArguments>(this->_arguments); }

Application& Application::with(ConsoleAdapter& consoleAdapter)
{
    this->_consoleAdapter = &consoleAdapter;
    return *this;
}

Application& Application::with(IArguments& args)
{
    this->_arguments = &args;
    return *this;
}
