#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

HelloWorld::HelloWorld() : message(ELROND_STR("Hello world")) {}

void HelloWorld::setup(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::setup"));

    if (ctx->arguments()->isString(ELROND_STR("message")))
    {
        this->message = ctx->arguments()->asString(ELROND_STR("message"));
    } 
}

void HelloWorld::start(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::start"));
}

void HelloWorld::loop(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::loop"));
    auto &me = *this;

    elrond::ctx(this)->console()->info(
        [&me](elrond::Stream& s)
        { s << ELROND_STR("Loop Message: ") << me.message; }
    );
}

void HelloWorld::stop(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::stop"));
}
