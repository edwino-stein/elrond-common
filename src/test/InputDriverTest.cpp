#include "test/InputDriverTest.hpp"

using elrond::test::InputDriverTest;
using elrond::module::BaseInputDriverModule;
using elrond::input::InputCallback;
using elrond::input::OnInputHandleT;

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
    const elrond::sizeT key, OnInputHandleT handle
){
    InputDriverTest::InputCallbackTestP testInput(new InputDriverTest::InputCallbackTest(handle));
    this->addInputListener(key, testInput.get());
    this->testInputCbInsts.push_back(std::move(testInput));
}

InputDriverTest::InputCallbackTest::InputCallbackTest(OnInputHandleT handle)
{
    this->handle = handle;
}
