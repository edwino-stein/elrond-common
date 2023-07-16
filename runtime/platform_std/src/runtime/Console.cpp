#include "runtime/Console.hpp"

using elrond::runtime::Console;
using elrond::interface::ConsoleAdapter;
using elrond::platform::ConsoleStream;

Console::Console(ConsoleAdapter& adapter, const elrond::string& tag)
: _adapter(&adapter), _tag(tag) {}

//
// Stream directly
//
elrond::platform::ConsoleStream Console::info() const
{ return { *(this->_adapter), this->_tag, ConsoleAdapter::INFO }; }

elrond::platform::ConsoleStream Console::error() const
{ return { *(this->_adapter), this->_tag, ConsoleAdapter::ERROR }; }

//
// Char and strings
//
void Console::info(char c) const { this->info() << c; }
void Console::info(unsigned char c) const { this->info() << c; }
void Console::info(const char* c) const { this->info() << c; }
void Console::info(elrond::string str) const { this->info() << str; }

void Console::error(const char* c) const { this->error() << c; }
void Console::error(elrond::string str) const { this->error() << str; }

//
// Numeric
//
void Console::info(int i) const { this->info() << i; }
void Console::info(unsigned int i) const { this->info() << i; }
void Console::info(long l) const { this->info() << l; }
void Console::info(unsigned long l) const { this->info() << l; }
void Console::info(double d) const { this->info() << d; }
