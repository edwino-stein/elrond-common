#include "runtime/Console.hpp"
#include "runtime/OStream.hpp"

#include <sstream>

using elrond::runtime::Console;
using elrond::interface::ConsoleAdapter;
using elrond::runtime::OStream;

Console::Console(elrond::string tag, ConsoleAdapter& adapter)
: tag(tag), adapter(&adapter) {}

//
// Stream handle
//
void Console::info(const elrond::StreamH& handle) const
{
    std::ostringstream oss;
    OStream stream(oss);
    handle(stream);

    this->adapter->info(oss, this->tag);
}

void Console::error(const elrond::StreamH& handle) const
{
    std::ostringstream oss;
    OStream stream(oss);
    handle(stream);

    this->adapter->error(oss, this->tag);
}

//
// Char and strings
//
void Console::info(const char c) const
{
    this->info(
        [&c](elrond::interface::Stream& s) { s << c; }
    );
}

void Console::info(const unsigned char c) const
{
    this->info(
        [&c](elrond::interface::Stream& s) { s << c; }
    );
}

void Console::info(const char c[]) const
{
    this->info(
        [&c](elrond::interface::Stream& s) { s << c; }
    );
}

void Console::info(elrond::string str) const
{
    this->info(
        [&str](elrond::interface::Stream& s) { s << str; }
    );
}

void Console::error(const char c[]) const
{
    this->error(
        [&c](elrond::interface::Stream& s) { s << c; }
    );
}

void Console::error(elrond::string str) const
{
    this->error(
        [&str](elrond::interface::Stream& s) { s << str; }
    );
}

//
// Numeric
//
void Console::info(const int i) const
{
    this->info(
        [&i](elrond::interface::Stream& s) { s << i; }
    );
}

void Console::info(const unsigned int i) const
{
    this->info(
        [&i](elrond::interface::Stream& s) { s << i; }
    );
}

void Console::info(const long l) const
{
    this->info(
        [&l](elrond::interface::Stream& s) { s << l; }
    );
}

void Console::info(const unsigned long l) const
{
    this->info(
        [&l](elrond::interface::Stream& s) { s << l; }
    );
}

void Console::info(const double d) const
{
    this->info(
        [&d](elrond::interface::Stream& s) { s << d; }
    );
}
