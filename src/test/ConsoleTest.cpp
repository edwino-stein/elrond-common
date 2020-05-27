#include "test/ConsoleTest.hpp"

using elrond::test::ConsoleTest;
using elrond::interface::Console;

ConsoleTest::ConsoleTest(ConsoleHandleT handle, const bool putEL):
handle(handle), oss(new std::ostringstream), putEL(putEL){}

const Console& ConsoleTest::operator<<(const char c) const
{
    this->getOSS() << c;
    return *this;
}

const Console& ConsoleTest::operator<<(const unsigned char c) const
{
    this->getOSS() << c;
    return *this;
}

const Console& ConsoleTest::operator<<(const char c[]) const
{
    this->getOSS() << c;
    return *this;
}

const Console& ConsoleTest::operator<<(elrond::String str) const
{
    this->getOSS() << str;
    return *this;
}

const Console& ConsoleTest::operator<<(const int i) const
{
    this->getOSS() << i;
    return *this;
}
const Console& ConsoleTest::operator<<(const unsigned int i) const
{
    this->getOSS() << i;
    return *this;
}

const Console& ConsoleTest::operator<<(const long l) const
{
    this->getOSS() << l;
    return *this;
}

const Console& ConsoleTest::operator<<(const unsigned long l) const
{
    this->getOSS() << l;
    return *this;
}

const Console& ConsoleTest::operator<<(const double d) const
{
    this->getOSS() << d;
    return *this;
}

const Console& ConsoleTest::operator<<(elrond::ConsoleCallbackT cb) const
{
    if(cb != nullptr) cb(*this);
    return *this;
}

const Console& ConsoleTest::endl() const
{
    std::ostringstream& oss = this->getOSS();

    if(this->putEL) oss << std::endl;
    if(this->handle != nullptr) this->handle(oss);

    oss.str("");
    oss.clear();

    return *this;
}

std::ostringstream& ConsoleTest::getOSS() const
{ return *(this->oss.get()); }
