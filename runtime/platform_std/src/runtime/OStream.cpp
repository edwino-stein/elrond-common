#include "runtime/OStream.hpp"

using elrond::runtime::OStream;
using elrond::interface::Stream;

OStream::OStream(std::ostream& os) : os(&os) {}

std::ostream& OStream::stream() const
{
    return *(this->os);
}

// Char and strings
Stream& OStream::operator<<(char c)
{
    this->stream() << c;
    return *this;
}

Stream& OStream::operator<<(unsigned char c)
{
    this->stream() << c;
    return *this;
}

Stream& OStream::operator<<(const char* c)
{
    this->stream() << c;
    return *this;
}

Stream& OStream::operator<<(elrond::string str)
{
    this->stream() << str;
    return *this;
}

// Numeric
 Stream& OStream::operator<<(int i)
{
    this->stream() << i;
    return *this;
}

 Stream& OStream::operator<<(unsigned int i)
{
    this->stream() << i;
    return *this;
}

Stream& OStream::operator<<(long l)
{
    this->stream() << l;
    return *this;
}

Stream& OStream::operator<<(unsigned long l)
{
    this->stream() << l;
    return *this;
}

Stream& OStream::operator<<(double d)
{
    this->stream() << d;
    return *this;
}
