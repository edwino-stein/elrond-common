#if !defined  _ELROND_INPUT_LISTENER_HPP
#define _ELROND_INPUT_LISTENER_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace input {

            class InputListener {

                protected:
                    elrond::input::OnInputHandleT handle = nullptr;
                    elrond::TaskContext* ctx = nullptr;

                public:

                    void init(
                        const elrond::sizeT key,
                        const elrond::sizeT inputMod,
                        elrond::input::OnInputHandleT handle,
                        elrond::TaskContext* const ctx = nullptr
                    );

                    void trigger(const elrond::word data);
            };
        }
    }

#endif
