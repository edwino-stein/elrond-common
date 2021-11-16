#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

void HelloWorld::setup()
{
    elrond::ctx(this).console().info("HelloWorld::setup\n");
}

void HelloWorld::start()
{
    elrond::ctx(this).console().info("HelloWorld::start\n");
}

void HelloWorld::loop()
{
    elrond::ctx(this).console().info("HelloWorld::loop\n");
}

void HelloWorld::stop()
{
    elrond::ctx(this).console().info("HelloWorld::stop\n");
}
