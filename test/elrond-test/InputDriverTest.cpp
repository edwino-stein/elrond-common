#include "elrond-test/InputDriverTest.hpp"

using elrond::test::InputDriverTest;
using elrond::modules::BaseInputDriverModule;
using elrond::input::InputCallback;

void InputDriverTest::addInputListener(const elrond::sizeT key, InputCallback *callback)
{
    auto it = this->inputMap.find(key);
    if(it != this->inputMap.end()) this->inputMap.erase(it);
    this->inputMap[key] = callback;
}

void InputDriverTest::trigger(const elrond::sizeT key, const elrond::word data) const
{
    auto it = this->inputMap.find(key);
    if(it == this->inputMap.end()) return;
    it->second->trigger(data);
}

void InputDriverTest::addInputListener(
    const elrond::sizeT key,
    std::function<void(const elrond::word data)> handle
){
    InputDriverTest::InputCallbackTestP testInput(new InputDriverTest::InputCallbackTest(handle));
    this->addInputListener(key, testInput.get());
    this->testInputCbInsts.push_back(std::move(testInput));
}

InputDriverTest::InputCallbackTest::InputCallbackTest(
    std::function<void(const elrond::word data)> handle
): _handle(handle)
{
    this->handle = [](elrond::word data, elrond::TaskContext *me)
    {
        ((InputDriverTest::InputCallbackTest*) me)->_handle(data);
    };

    this->ctx = this;
}
