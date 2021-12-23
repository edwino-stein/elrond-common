#include "test/InputTriggerTest.hpp"
#include "test/InputTest.hpp"

using elrond::test::InputTriggerTest;
using elrond::test::InputTest;

InputTriggerTest::InputTriggerTest(const elrond::sizeT key, InputTest& inputMod):
_key(key), inputMod(inputMod) {}

elrond::sizeT InputTriggerTest::key() const { return this->_key; }

void InputTriggerTest::trigger(const elrond::word data)
{ this->inputMod.triggerInput(this, data); }
