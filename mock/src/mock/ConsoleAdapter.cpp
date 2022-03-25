#include "mock/ConsoleAdapter.hpp"

using elrond::mock::ConsoleAdapter;

ConsoleAdapter::ConsoleAdapter()
:
    printInfoH([](std::ostringstream&){}),
    throwErrorH(ConsoleAdapter::defaultThrowError)
{}

ConsoleAdapter::ConsoleAdapter(const CallbackStream& printInfoH)
:
    printInfoH(printInfoH),
    throwErrorH(ConsoleAdapter::defaultThrowError)
{}

ConsoleAdapter::ConsoleAdapter(
    const CallbackStream& printInfoH,
    const CallbackStream throwErrorH
):
    printInfoH(printInfoH),
    throwErrorH(throwErrorH)
{}

void ConsoleAdapter::info(std::ostringstream& msg, const std::string&) const
{
    this->printInfoH(msg);
}

void ConsoleAdapter::error(std::ostringstream& msg, const std::string&) const
{
    this->throwErrorH(msg);
}

ConsoleAdapter* ConsoleAdapter::null()
{
    static ConsoleAdapter nullSingleton;
    return &nullSingleton;
}

void ConsoleAdapter::defaultThrowError(std::ostringstream& msg)
{
    throw std::runtime_error(msg.str());
}
