#if !defined  _ELROND_INPUT_TRIGGER_TEST_HPP
#define _ELROND_INPUT_TRIGGER_TEST_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class InputTriggerTest {

                protected:

                    const elrond::sizeT _key;
                    elrond::test::InputTest& inputMod;

                public:

                    InputTriggerTest(const elrond::sizeT key,
                                     elrond::test::InputTest& inputMod);

                    elrond::sizeT key() const;
                    void trigger(const elrond::word data);
            };
        }
    }

#endif
