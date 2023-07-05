#include "runtime/NullStream.hpp"

using elrond::runtime::NullStream;

// Char and strings
const elrond::interface::Stream& NullStream::operator<<(char) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(unsigned char) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(const char*) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(elrond::string) const { return *this; }

// Numeric
const elrond::interface::Stream& NullStream::operator<<(int) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(unsigned int) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(long) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(unsigned long) const { return *this; }
const elrond::interface::Stream& NullStream::operator<<(double) const { return *this; }
