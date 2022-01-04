#include "input/InputListener.hpp"
#include "interface/Runtime.hpp"
#include "module/BaseInputModule.hpp"

/*  ****************************************************************************
    **************** elrond::input::InputListener Implementation ***************
    ****************************************************************************/

namespace elrond {
    namespace input {

        ELROND_INLINE_FUNC void InputListener::init(
            const elrond::sizeT key,
            const elrond::sizeT inputMod,
            OnInputHandleT handle,
            elrond::TaskContext* const ctx
        ){
            if(this->handle != nullptr) return;
            this->handle = handle;
            this->ctx = ctx;
            elrond::app().getInput(inputMod).addInputListener(key, this);
        }

        ELROND_INLINE_FUNC void InputListener::trigger(const elrond::word data)
        { if(this->handle != nullptr) this->handle(data, this->ctx); }
    }
}
