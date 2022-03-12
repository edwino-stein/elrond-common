#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

void HelloWorld::setup(const elrond::Parameters& param)
{
    elrond::ctx(this)->console()->info("HelloWorld::setup");
    if (param.isString("message")) this->message = param.asString("message");
}

void HelloWorld::start()
{
    elrond::ctx(this)->console()->info("HelloWorld::start");
}

void HelloWorld::loop()
{
    elrond::ctx(this)->console()->info("HelloWorld::loop");
    auto &me = *this;
    elrond::ctx(this)->console()->info(
        [&me](elrond::Stream& s)
        { s << "Loop Message: " << me.message; }
    );
}

void HelloWorld::stop()
{
    elrond::ctx(this)->console()->info("HelloWorld::stop");
}
