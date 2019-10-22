#include "runtime/InputCallback.hpp"
#include "interfaces/RuntimeInterface.hpp"
#include "modules/BaseInputDriverModule.hpp"

using elrond::input::InputCallback;
using elrond::input::onInputT;
using elrond::modules::BaseInputDriverModule;

/*  ****************************************************************************
    ************** Implementation for elrond::input::InputCallback *************
    ****************************************************************************/

InputCallback::InputCallback(){}

void InputCallback::init(const elrond::sizeT key, const elrond::sizeT inService, onInputT handle, elrond::TaskContext *ctx){
    BaseInputDriverModule &input = elrond::app().getInputService(inService);
    input.addInputListener(key, this);
    this->handle = handle;
    this->ctx = ctx;
}

void InputCallback::trigger(const elrond::word data){ this->handle(data, this->ctx); }
