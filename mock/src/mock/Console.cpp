#include "mock/Console.hpp"
#include "mock/StringStream.hpp"

using elrond::mock::Console;
using elrond::interface::Stream;
using elrond::mock::StringStream;

Console::Console()
:
    printInfoH([](elrond::StreamH){}),
    throwErrorH(Console::defaultThrowError)
{}

Console::Console(const CallbackStream& printInfoH)
:
    printInfoH(printInfoH),
    throwErrorH(Console::defaultThrowError)
{}

Console::Console(
    const CallbackStream& printInfoH,
    const CallbackStream throwErrorH
):
    printInfoH(printInfoH),
    throwErrorH(throwErrorH)
{}

void Console::printInfo(const elrond::StreamH& handle) const
{
    this->printInfoH(handle);
}

void Console::throwError(const elrond::StreamH& handle) const
{
    this->throwErrorH(handle);
}

std::shared_ptr<elrond::interface::Console> Console::null()
{
    return std::make_shared<Console>();
}

void Console::defaultThrowError(elrond::StreamH handle)
{
    StringStream ss;
    handle(ss);
    throw std::runtime_error(ss.getString());
}
