#include "runtime/BaseConsole.hpp"

using elrond::runtime::BaseConsole;
using elrond::interface::Stream;


//
// Stream handle
//
void BaseConsole::info(const elrond::StreamH& handle) const
{
    this->printInfo(handle);
}

void BaseConsole::error(const elrond::StreamH& handle) const
{
    this->throwError(handle);
}

//
// Char and strings
//
void BaseConsole::info(const char c) const
{
    this->printInfo([&c](Stream& s) { s << c; });
}

void BaseConsole::info(const unsigned char c) const
{
    this->printInfo([&c](Stream& s) { s << c; });
}

void BaseConsole::info(const char c[]) const
{
    this->printInfo([&c](Stream& s) { s << c; });
}

void BaseConsole::info(elrond::string str) const
{
    this->printInfo([&str](Stream& s) { s << str; });
}

void BaseConsole::error(const char c[]) const
{
    this->throwError([&c](Stream& s) { s << c; });
}

void BaseConsole::error(elrond::string str) const
{
    this->throwError([&str](Stream& s) { s << str; });
}

//
// Numeric
//
void BaseConsole::info(const int i) const
{
    this->printInfo([&i](Stream& s) { s << i; });
}

void BaseConsole::info(const unsigned int i) const
{
    this->printInfo([&i](Stream& s) { s << i; });
}

void BaseConsole::info(const long l) const
{
    this->printInfo([&l](Stream& s) { s << l; });
}

void BaseConsole::info(const unsigned long l) const
{
    this->printInfo([&l](Stream& s) { s << l; });
}

void BaseConsole::info(const double d) const
{
    this->printInfo([&d](Stream& s) { s << d; });
}
