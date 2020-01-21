#if !defined  _ELROND_INPUT_CALLBACK_HPP
#define _ELROND_INPUT_CALLBACK_HPP

    #include "types.hpp"

    namespace elrond {
        namespace input {

            class InputCallback {

                protected:

                    elrond::input::OnInputHandleT handle;
                    elrond::TaskContext* ctx = nullptr;

                public:

                    InputCallback();

                    void init(
                        const elrond::sizeT key,
                        const elrond::sizeT inService,
                        elrond::input::OnInputHandleT handle,
                        elrond::TaskContext* const ctx = nullptr
                    );

                    void trigger(const elrond::word data);
            };
        }
    }

#endif
