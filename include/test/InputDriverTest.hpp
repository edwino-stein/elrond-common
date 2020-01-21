#if !defined  _ELROND_TEST_INPUT_DRIVER_HPP
#define _ELROND_TEST_INPUT_DRIVER_HPP

    #include "elrond.hpp"

    #include <map>
    #include <vector>
    #include <memory>

    namespace elrond {
        namespace test {

            class InputDriverTest : public elrond::module::BaseInputDriverModule {

                private:

                    class InputCallbackTest: public elrond::input::InputCallback {
                        public:
                            InputCallbackTest(elrond::input::OnInputHandleT handle);
                    };

                    using InputCallbackTestP = std::unique_ptr<InputCallbackTest>;

                protected:

                    std::map<elrond::sizeT, elrond::input::InputCallback*> inputMap;
                    std::vector<InputCallbackTestP> testInputCbInsts;

                public:

                    void addInputListener(const elrond::sizeT key, elrond::input::InputCallback *callback) override;
                    void trigger(const elrond::sizeT key, const elrond::word data) const;
                    void addInputListener(const elrond::sizeT key, elrond::input::OnInputHandleT handle);
            };
        }
    }

#endif
