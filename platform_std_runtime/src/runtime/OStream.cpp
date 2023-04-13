#include "runtime/OStream.hpp"

using elrond::runtime::OStream;
using elrond::interface::Stream;

OStream::OStream(std::ostream& os) : os(&os) {}

std::ostream& OStream::stream() const
{
    return *(this->os);
}

// Char and strings
const Stream& OStream::operator<<(char c) const
{
    this->stream() << c;
    return *this;
}

const Stream& OStream::operator<<(unsigned char c) const
{
    this->stream() << c;
    return *this;
}

const Stream& OStream::operator<<(const char* c) const
{
    this->stream() << c;
    return *this;
}

const Stream& OStream::operator<<(elrond::string str) const
{
    this->stream() << str;
    return *this;
}

// Numeric
const Stream& OStream::operator<<(int i) const
{
    this->stream() << i;
    return *this;
}

const Stream& OStream::operator<<(unsigned int i) const
{
    this->stream() << i;
    return *this;
}

const Stream& OStream::operator<<(long l) const
{
    this->stream() << l;
    return *this;
}

const Stream& OStream::operator<<(unsigned long l) const
{
    this->stream() << l;
    return *this;
}

const Stream& OStream::operator<<(double d) const
{
    this->stream() << d;
    return *this;
}
