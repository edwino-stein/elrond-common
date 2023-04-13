#include "runtime/NullStream.hpp"

using elrond::runtime::NullStream;
using elrond::interface::Stream;

NullStream::NullStream() {}

// Char and strings
const Stream& NullStream::operator<<(char) const { return *this; }
const Stream& NullStream::operator<<(unsigned char) const { return *this; }
const Stream& NullStream::operator<<(const char*) const { return *this; }
const Stream& NullStream::operator<<(elrond::string) const { return *this; }

// Numeric
const Stream& NullStream::operator<<(int) const { return *this; }
const Stream& NullStream::operator<<(unsigned int) const { return *this; }
const Stream& NullStream::operator<<(long) const { return *this; }
const Stream& NullStream::operator<<(unsigned long) const { return *this; }
const Stream& NullStream::operator<<(double) const { return *this; }
