#include "test/DebugOut.hpp"

using elrond::test::DebugOut;
using elrond::interfaces::DebugOutInterface;

DebugOut::DebugOut(DebugOutHandleT handle): handle(handle) {}

const DebugOutInterface& DebugOut::put(const char c[]) const
{
    std::ostringstream oss;
    oss << c;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(char c) const
{
    std::ostringstream oss;
    oss << c;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(unsigned char c) const
{
    std::ostringstream oss;
    oss << c;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(int i) const
{
    std::ostringstream oss;
    oss << i;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(unsigned int i) const
{
    std::ostringstream oss;
    oss << i;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(long l) const
{
    std::ostringstream oss;
    oss << l;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(unsigned long l) const
{
    std::ostringstream oss;
    oss << l;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::put(double d) const
{
    std::ostringstream oss;
    oss << d;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(const char c[]) const
{
    std::ostringstream oss;
    oss << c << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(char c) const
{
    std::ostringstream oss;
    oss << c << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(unsigned char c) const
{
    std::ostringstream oss;
    oss << c << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(int i) const
{
    std::ostringstream oss;
    oss << i << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(unsigned int i) const
{
    std::ostringstream oss;
    oss << i << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(long l) const
{
    std::ostringstream oss;
    oss << l << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(unsigned long l) const
{
    std::ostringstream oss;
    oss << l << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn(double d) const
{
    std::ostringstream oss;
    oss << d << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::putLn() const
{
    std::ostringstream oss;
    oss << std::endl;
    this->handle(oss);
    return *this;
}

const DebugOutInterface& DebugOut::flush() const { return *this; }

#ifdef ELROND_WITH_STR_TYPE

    const DebugOutInterface& DebugOut::put(elrond::String str) const
    {
        std::ostringstream oss;
        oss << str;
        this->handle(oss);
        return *this;
    }

    const DebugOutInterface& DebugOut::putLn(elrond::String str) const
    {
        std::ostringstream oss;
        oss << str << std::endl;
        this->handle(oss);
        return *this;
    }

#endif
