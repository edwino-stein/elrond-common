#include "runtime/Console.hpp"

using elrond::runtime::Console;
using elrond::interface::ConsoleAdapter;
using elrond::platform::ConsoleStream;

Console::Console(elrond::string, ConsoleAdapter& adapter) : adapter(adapter) {}
Console::Console(ConsoleAdapter& adapter) : adapter(adapter) {}

const elrond::platform::ConsoleStream Console::info() const
{
    return this->adapter.getInfoStreamAdapter();
}

const elrond::platform::ConsoleStream Console::error() const
{
    return this->adapter.getErrorStreamAdapter();
}

//
// Stream handle
//
void Console::info(const elrond::StreamH&) const
{}

void Console::error(const elrond::StreamH&) const
{}

//
// Char and strings
//
void Console::info(const char c) const { this->info() << c; }
void Console::info(const unsigned char c) const { this->info() << c; }
void Console::info(const char c[]) const { this->info() << c; }
void Console::info(elrond::string str) const { this->info() << str; }

void Console::error(const char c[]) const { this->error() << c; }
void Console::error(elrond::string str) const { this->error() << str; }

//
// Numeric
//
void Console::info(const int i) const { this->info() << i; }
void Console::info(const unsigned int i) const { this->info() << i; }
void Console::info(const long l) const { this->info() << l; }
void Console::info(const unsigned long l) const { this->info() << l; }
void Console::info(const double d) const { this->info() << d; }
