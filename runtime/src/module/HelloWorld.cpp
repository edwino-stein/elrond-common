#include "module/HelloWorld.hpp"

using elrond::module::HelloWorld;

#ifndef ELROND_DISABLE_DESTRUCTORS
    HelloWorld::~HelloWorld(){}
#endif

void HelloWorld::setup()
{
    std::cout << "HelloWorld::setup" << "\n"; 
}

void HelloWorld::start()
{
    std::cout << "HelloWorld::start" << "\n"; 
}

void HelloWorld::loop()
{
    std::cout << "HelloWorld::loop" << "\n"; 
}

void HelloWorld::stop()
{
    std::cout << "HelloWorld::stop" << "\n"; 
}
