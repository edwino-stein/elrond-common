#if !defined  _ELROND_TEST_RUNTIME_HPP
#define _ELROND_TEST_RUNTIME_HPP

    #include "elrond.hpp"

    #include <functional>
    #include <vector>

    namespace elrond {
        namespace test {

            class RuntimeTest : public elrond::interface::Runtime {

                protected:

                    elrond::modules::BaseGpioModule* gpio = nullptr;
                    elrond::modules::BaseInputDriverModule* input = nullptr;
                    elrond::channel::BaseChannelManager* chmgr = nullptr;
                    elrond::interface::DebugOut* debugOut = nullptr;

                public:

                    const RuntimeTest& init(
                        elrond::interface::Module& inst,
                        elrond::interface::ConfigMap &cfg
                    ) const;

                    const RuntimeTest& start(
                        elrond::interface::Module& inst,
                        std::function<bool()> loopContinue
                    ) const;

                    elrond::modules::BaseGpioModule &getGpioService() const override;
                    elrond::modules::BaseInputDriverModule &getInputService(const elrond::sizeT id = 0) const override;
                    elrond::channel::BaseChannelManager &getChannelManager(const elrond::sizeT id = 0) const override;
                    const elrond::interface::DebugOut &dout() const override;

                    void onError(const char *error) override;

                    #ifdef ELROND_WITH_STR_TYPE
                        void onError(elrond::String error) override;
                    #endif

                    RuntimeTest& set(elrond::modules::BaseGpioModule& gpio);
                    RuntimeTest& set(elrond::modules::BaseInputDriverModule &input);
                    RuntimeTest& set(elrond::channel::BaseChannelManager &chmgr);
                    RuntimeTest& set(elrond::interface::DebugOut &dout);

                    static void setAppInstance(elrond::interface::Runtime* app);
            };
        }
    }

#endif
