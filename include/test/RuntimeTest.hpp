#if !defined  _ELROND_TEST_RUNTIME_HPP
#define _ELROND_TEST_RUNTIME_HPP

    #include "elrond.hpp"

    #include <functional>
    #include <vector>

    namespace elrond {
        namespace test {

            class RuntimeTest : public elrond::interface::Runtime {

                protected:

                    elrond::module::BaseGpioModule* gpio = nullptr;
                    elrond::module::BaseInputDriverModule* input = nullptr;
                    elrond::interface::ChannelManager* chmgr = nullptr;
                    elrond::interface::DebugOut* debugOut = nullptr;

                public:

                    const RuntimeTest& init(
                        elrond::interface::Module& inst,
                        elrond::interface::ConfigMap &cfg,
                        elrond::LoopControl& lc
                    ) const;

                    const RuntimeTest& start(
                        elrond::interface::Module& inst,
                        elrond::LoopControl& lc,
                        std::function<bool()> loopContinue
                    ) const;

                    elrond::module::BaseGpioModule &getGpioService() const override;
                    elrond::module::BaseInputDriverModule &getInputService(const elrond::sizeT id = 0) const override;
                    elrond::interface::ChannelManager &getChannelManager(const elrond::sizeT id = 0) const override;
                    const elrond::interface::DebugOut &dout() const override;

                    void onError(const char *error) override;

                    #ifdef ELROND_WITH_STR_TYPE
                        void onError(elrond::String error) override;
                    #endif

                    RuntimeTest& set(elrond::module::BaseGpioModule& gpio);
                    RuntimeTest& set(elrond::module::BaseInputDriverModule& input);
                    RuntimeTest& set(elrond::interface::ChannelManager& chmgr);
                    RuntimeTest& set(elrond::interface::DebugOut& dout);

                    static void setAppInstance(elrond::interface::Runtime* app);
            };
        }
    }

#endif
