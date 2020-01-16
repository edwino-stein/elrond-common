#if !defined  _ELROND_TEST_RUNTIME_HPP
#define _ELROND_TEST_RUNTIME_HPP

    #include "elrond.hpp"

    #include <functional>
    #include <vector>

    namespace elrond {
        namespace test {

            class RuntimeTest : public elrond::interfaces::RuntimeInterface {

                protected:

                    elrond::modules::BaseGpioModule* gpio = nullptr;
                    elrond::modules::BaseInputDriverModule* input = nullptr;
                    elrond::channel::BaseChannelManager* chmgr = nullptr;
                    elrond::interfaces::DebugOutInterface* debugOut = nullptr;

                    elrond::interfaces::ModuleInterface* module;

                public:

                    const RuntimeTest& init(
                        elrond::interfaces::ModuleInterface& inst,
                        elrond::interfaces::ConfigMapInterface &cfg
                    ) const;

                    const RuntimeTest& start(
                        elrond::interfaces::ModuleInterface& inst,
                        std::function<bool()> loopContinue
                    ) const;

                    elrond::modules::BaseGpioModule &getGpioService() const override;
                    elrond::modules::BaseInputDriverModule &getInputService(const elrond::sizeT id = 0) const override;
                    elrond::channel::BaseChannelManager &getChannelManager(const elrond::sizeT id = 0) const override;
                    const elrond::interfaces::DebugOutInterface &dout() const override;
                    void onError(const char *error) override;

                    RuntimeTest& set(elrond::modules::BaseGpioModule& gpio);
                    RuntimeTest& set(elrond::modules::BaseInputDriverModule &input);
                    RuntimeTest& set(elrond::channel::BaseChannelManager &chmgr);
                    RuntimeTest& set(elrond::interfaces::DebugOutInterface &dout);

                    static void setAppInstance(elrond::interfaces::RuntimeInterface* app);
            };
        }
    }

#endif
