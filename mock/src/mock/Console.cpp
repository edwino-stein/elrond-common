#include "mock/Console.hpp"

using elrond::mock::Console;
using elrond::interface::Stream;

Console::Console()
:
    printInfoH([](elrond::StreamH){})
{}

Console::Console(const elrond::procedure<elrond::StreamH>& printInfoH)
:
    printInfoH(printInfoH)
{}

void Console::printInfo(const elrond::StreamH& handle) const
{
    this->printInfoH(handle);
}
