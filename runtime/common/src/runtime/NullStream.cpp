#include "runtime/NullStream.hpp"

using elrond::runtime::NullStream;

// Char and strings
elrond::interface::Stream& NullStream::operator<<(char) { return *this; }
elrond::interface::Stream& NullStream::operator<<(unsigned char) { return *this; }
elrond::interface::Stream& NullStream::operator<<(const char*) { return *this; }
elrond::interface::Stream& NullStream::operator<<(elrond::string) { return *this; }

// Numeric
elrond::interface::Stream& NullStream::operator<<(int) { return *this; }
elrond::interface::Stream& NullStream::operator<<(unsigned int) { return *this; }
elrond::interface::Stream& NullStream::operator<<(long) { return *this; }
elrond::interface::Stream& NullStream::operator<<(unsigned long) { return *this; }
elrond::interface::Stream& NullStream::operator<<(double) { return *this; }
