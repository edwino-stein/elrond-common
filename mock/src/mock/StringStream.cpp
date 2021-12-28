#include "mock/StringStream.hpp"

using elrond::mock::StringStream;
using elrond::interface::Stream;

StringStream::StringStream() : oss(new std::ostringstream)
{
    this->flush();
}

std::ostringstream& StringStream::stream() const
{
    return *(this->oss);
}

// Char and strings
const Stream& StringStream::operator<<(const char c) const
{
    this->stream() << c;
    return *this;
}

const Stream& StringStream::operator<<(const unsigned char c) const
{
    this->stream() << c;
    return *this;
}

const Stream& StringStream::operator<<(const char c[]) const
{
    this->stream() << c;
    return *this;
}

const Stream& StringStream::operator<<(elrond::string str) const
{
    this->stream() << str;
    return *this;
}

// Numeric
const Stream& StringStream::operator<<(const int i) const
{
    this->stream() << i;
    return *this;
}

const Stream& StringStream::operator<<(const unsigned int i) const
{
    this->stream() << i;
    return *this;
}

const Stream& StringStream::operator<<(const long l) const
{
    this->stream() << l;
    return *this;
}

const Stream& StringStream::operator<<(const unsigned long l) const
{
    this->stream() << l;
    return *this;
}

const Stream& StringStream::operator<<(const double d) const
{
    this->stream() << d;
    return *this;
}

// Util
std::string StringStream::getString() const
{
    return this->stream().str();
}

void StringStream::flush()
{
    this->stream().str("");
    this->stream().clear();
}
