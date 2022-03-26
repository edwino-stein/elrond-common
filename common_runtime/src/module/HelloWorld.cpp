#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

HelloWorld::HelloWorld()
:
    message(ELROND_STR("Hello world")),
    interval(1000),
    mode(ELROND_STR("sync"))
{}

void HelloWorld::setup(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::setup"));
    auto args = ctx->arguments();

    elrond::string field = ELROND_STR("message");
    if (args->isString(field))
    {
        this->message = args->asString(field);
    }

    field = ELROND_STR("async");
    if (args->isBool(field) && args->asBool(field))
    {
        this->mode = ELROND_STR("async");
        ctx->loopAsync(true);
    }

    field = ELROND_STR("interval");
    if (args->isInt(field))
    {
        this->interval = args->asInt(field);
    }
    ctx->loopInterval(this->interval);

    field = ELROND_STR("loop");
    ctx->loopEnable(
        args->isBool(field) ? args->asBool(field) : true
    );
}

void HelloWorld::start(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::start"));
}

void HelloWorld::loop(elrond::ContextP ctx)
{
    auto console = ctx->console();
    auto me = this;

    console->info(ELROND_STR("HelloWorld::loop"));
    console->info(
        [&me](elrond::Stream& s)
        {
            s   << ELROND_STR("Loop Message [") 
                << me->mode << '|' << me->interval
                << ELROND_STR("]: ") << me->message;
        }
    );
}

void HelloWorld::stop(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::stop"));
}
