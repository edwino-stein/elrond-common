#include "runtime/NullStream.hpp"

using elrond::runtime::NullStream;
using elrond::interface::Stream;

NullStream::NullStream() {}

// Char and strings
const Stream& NullStream::operator<<(const char) const { return *this; }
const Stream& NullStream::operator<<(const unsigned char) const { return *this; }
const Stream& NullStream::operator<<(const char[]) const { return *this; }
const Stream& NullStream::operator<<(elrond::string) const { return *this; }

// Numeric
const Stream& NullStream::operator<<(const int) const { return *this; }
const Stream& NullStream::operator<<(const unsigned int) const{ return *this; }
const Stream& NullStream::operator<<(const long) const{ return *this; }
const Stream& NullStream::operator<<(const unsigned long) const { return *this; }
const Stream& NullStream::operator<<(const double) const { return *this; }
