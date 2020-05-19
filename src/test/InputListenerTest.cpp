#include "test/InputListenerTest.hpp"

using elrond::test::InputListenerTest;
using elrond::input::OnInputHandleT;
using elrond::module::BaseInputModule;

InputListenerTest::InputListenerTest(
    const elrond::sizeT key,
    OnInputHandleT handle,
    BaseInputModule& inputMod
){
    this->handle = handle;
    inputMod.addInputListener(key, this);
}
