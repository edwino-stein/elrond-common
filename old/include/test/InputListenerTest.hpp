#if !defined  _ELROND_INPUT_LISTENER_TEST_HPP
#define _ELROND_INPUT_LISTENER_TEST_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class InputListenerTest : public elrond::input::InputListener {

                public:

                    InputListenerTest(const elrond::sizeT key,
                                      elrond::input::OnInputHandleT handle,
                                      elrond::module::BaseInputModule& inputMod);

                    void init(
                        const elrond::sizeT key,
                        const elrond::sizeT inputMod,
                        elrond::input::OnInputHandleT handle,
                        elrond::TaskContext* const ctx
                    ) = delete;
            };
        }
    }

#endif
