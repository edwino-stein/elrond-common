#if !defined  _ELROND_TEST_INPUT_HPP
#define _ELROND_TEST_INPUT_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class InputTest : public elrond::module::BaseInputModule {

                protected:

                    using InputListenerCollection = std::vector<elrond::input::InputListener*>;
                    using InputListenerCollectionP = std::unique_ptr<InputListenerCollection>;
                    std::map<elrond::sizeT, InputListenerCollectionP> inputMap;

                public:

                    void addInputListener(const elrond::sizeT key,
                                          elrond::input::InputListener* listener) override;

                    void triggerInput(elrond::test::InputTriggerTest* trigger,
                                      const elrond::word data);
            };
        }
    }

#endif
