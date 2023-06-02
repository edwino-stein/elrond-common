#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

HelloWorld::HelloWorld()
:
    message(ELROND_STR("Hello world")),
    interval(1000)
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

    field = ELROND_STR("loop");
    if (args->isBool(field) ? args->asBool(field) : true)
    {
        field = ELROND_STR("interval");
        this->interval = args->isInt(field) ? args->asInt(field) : this->interval;
        ctx->setLoopEvery(elrond::milliseconds(this->interval));
    }
}

void HelloWorld::start(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::start"));
}

void HelloWorld::loop(elrond::ContextP ctx)
{
    auto console = ctx->console();
    console->info(ELROND_STR("HelloWorld::loop"));
    console->info() << ELROND_STR("Loop Message [")
                    << this->interval
                    << ELROND_STR(" ms]: ")
                    << this->message;
}

void HelloWorld::stop(elrond::ContextP ctx)
{
    ctx->console()->info(ELROND_STR("HelloWorld::stop"));
}
