#include "test/DebugOutTest.hpp"

using elrond::test::DebugOutTest;
using elrond::interface::DebugOut;

DebugOutTest::DebugOutTest(DebugOutHandleT handle): handle(handle) {}

const DebugOut& DebugOutTest::put(const char c[]) const
{
    std::ostringstream oss;
    oss << c;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(char c) const
{
    std::ostringstream oss;
    oss << c;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(unsigned char c) const
{
    std::ostringstream oss;
    oss << c;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(int i) const
{
    std::ostringstream oss;
    oss << i;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(unsigned int i) const
{
    std::ostringstream oss;
    oss << i;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(long l) const
{
    std::ostringstream oss;
    oss << l;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(unsigned long l) const
{
    std::ostringstream oss;
    oss << l;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::put(double d) const
{
    std::ostringstream oss;
    oss << d;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(const char c[]) const
{
    std::ostringstream oss;
    oss << c << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(char c) const
{
    std::ostringstream oss;
    oss << c << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(unsigned char c) const
{
    std::ostringstream oss;
    oss << c << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(int i) const
{
    std::ostringstream oss;
    oss << i << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(unsigned int i) const
{
    std::ostringstream oss;
    oss << i << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(long l) const
{
    std::ostringstream oss;
    oss << l << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(unsigned long l) const
{
    std::ostringstream oss;
    oss << l << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn(double d) const
{
    std::ostringstream oss;
    oss << d << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::putLn() const
{
    std::ostringstream oss;
    oss << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOut& DebugOutTest::flush() const { return *this; }

#ifdef ELROND_WITH_STR_TYPE

    const DebugOut& DebugOutTest::put(elrond::String str) const
    {
        std::ostringstream oss;
        oss << str;
        this->handle(oss);
        return *this;
    }

    const DebugOut& DebugOutTest::putLn(elrond::String str) const
    {
        std::ostringstream oss;
        oss << str << std::endl;
        this->handle(oss);
        return *this;
    }

#endif
