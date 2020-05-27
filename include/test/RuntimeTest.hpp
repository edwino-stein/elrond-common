#if !defined  _ELROND_TEST_RUNTIME_HPP
#define _ELROND_TEST_RUNTIME_HPP

    #include "elrond_test_types.hpp"
    #include "test/ConsoleTest.hpp"

    namespace elrond {
        namespace test {

            class RuntimeTest : public elrond::interface::Runtime {

                protected:

                    elrond::module::BaseGpioModule* gpio = nullptr;
                    elrond::module::BaseInputModule* input = nullptr;
                    elrond::channel::BaseChannelManager* chmgr = nullptr;
                    elrond::interface::Console* console = nullptr;

                    bool autoSync = true;

                    static ConsoleTest builtInConsole;

                public:

                    RuntimeTest(const bool defaultApp = true);
                    virtual ~RuntimeTest();

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

                    elrond::module::BaseGpioModule &getGpio() const override;
                    elrond::module::BaseInputModule &getInput(const elrond::sizeT id = 0) const override;
                    elrond::interface::ChannelManager &getChannelManager(const elrond::sizeT id = 0) const override;
                    const elrond::interface::Console &getInfoConsole() const override;

                    void onError(const char *error) override;

                    #ifdef ELROND_WITH_STR_TYPE
                        void onError(elrond::String error) override;
                    #endif

                    RuntimeTest& set(elrond::module::BaseGpioModule& gpio);
                    RuntimeTest& set(elrond::module::BaseInputModule& input);
                    RuntimeTest& set(elrond::interface::Console& console);

                    RuntimeTest& set(elrond::channel::BaseChannelManager& chmgr,
                                     const bool autoSync = true);

                    static void setAppInstance(elrond::interface::Runtime& app);
                    static void setAppInstance(elrond::interface::Runtime* app);
                    static ConsoleTest& getBuiltInConsole();
            };
        }
    }

#endif
