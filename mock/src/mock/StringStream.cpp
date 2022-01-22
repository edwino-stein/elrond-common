#include "mock/StringStream.hpp"

using elrond::mock::StringStream;
using elrond::platform::OStream;

StringStream::StringStream() : OStream(oss)
{
    this->flush();
}

// Util
std::string StringStream::getString() const
{
    return this->oss.str();
}

void StringStream::flush()
{
    this->oss.str("");
    this->oss.clear();
}
