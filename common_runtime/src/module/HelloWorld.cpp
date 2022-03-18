#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

HelloWorld::HelloWorld() : message(ELROND_STR("Hello world")) {}

void HelloWorld::setup(const elrond::Parameters& param)
{
    elrond::ctx(this)->console()->info(ELROND_STR("HelloWorld::setup"));

    if (param.isString(ELROND_STR("message")))
    {
        this->message = param.asString(ELROND_STR("message"));
    } 
}

void HelloWorld::start()
{
    elrond::ctx(this)->console()->info(ELROND_STR("HelloWorld::start"));
}

void HelloWorld::loop()
{
    elrond::ctx(this)->console()->info(ELROND_STR("HelloWorld::loop"));
    auto &me = *this;

    elrond::ctx(this)->console()->info(
        [&me](elrond::Stream& s)
        { s << ELROND_STR("Loop Message: ") << me.message; }
    );
}

void HelloWorld::stop()
{
    elrond::ctx(this)->console()->info(ELROND_STR("HelloWorld::stop"));
}
