#include "input/InputCallback.hpp"
#include "interface/Runtime.hpp"
#include "module/BaseInputDriverModule.hpp"

/*  ****************************************************************************
    **************** elrond::input::InputCallback Implementation ***************
    ****************************************************************************/

namespace elrond {
    namespace input {

        ELROND_INLINE_FUNC InputCallback::InputCallback(){}

        ELROND_INLINE_FUNC void InputCallback::init(
            const elrond::sizeT key,
            const elrond::sizeT inService,
            OnInputHandleT handle,
            elrond::TaskContext* const ctx
        ){
            elrond::app().getInputService(inService).addInputListener(key, this);
            this->handle = handle;
            this->ctx = ctx;
        }

        ELROND_INLINE_FUNC void InputCallback::trigger(const elrond::word data)
        { this->handle(data, this->ctx); }
    }
}
