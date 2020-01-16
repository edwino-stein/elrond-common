#if !defined  _ELROND_TEST_INPUT_DRIVER_HPP
#define _ELROND_TEST_INPUT_DRIVER_HPP

    #include "elrond.hpp"

    #include <map>
    #include <functional>
    #include <vector>
    #include <memory>

    namespace elrond {
        namespace test {

            class InputDriverTest : public elrond::modules::BaseInputDriverModule {

                private:

                    class InputCallbackTest: public elrond::input::InputCallback, public elrond::TaskContext {
                        protected:
                            std::function<void(const elrond::word data)> _handle;

                        public:
                            InputCallbackTest(std::function<void(const elrond::word data)> handle);
                    };

                    using InputCallbackTestP = std::unique_ptr<InputCallbackTest>;

                protected:

                    std::map<const elrond::sizeT, elrond::input::InputCallback*> inputMap;
                    std::vector<InputCallbackTestP> testInputCbInsts;

                public:

                    void addInputListener(const elrond::sizeT key, elrond::input::InputCallback *callback) override;
                    void trigger(const elrond::sizeT key, const elrond::word data) const;

                    void addInputListener(const elrond::sizeT key, std::function<void(const elrond::word data)> handle);
            };
        }
    }

#endif
