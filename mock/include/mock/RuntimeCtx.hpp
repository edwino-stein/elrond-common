#ifndef ELROND_MOCK_RUNTIME_CTX_HPP
    #define ELROND_MOCK_RUNTIME_CTX_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class RuntimeCtx
            {
                public:

                    class Context : public elrond::interface::Context
                    {
                        public:

                            RuntimeCtx& ctx;

                            Context(RuntimeCtx& ctx);

                            elrond::pointer<elrond::interface::Console>
                            console() const override;

                            elrond::pointer<elrond::interface::Arguments>
                            arguments() const override;

                            elrond::string name() const override;

                            void setLoopEvery(const elrond::TimeSpan& ts) override;
                            void unsetLoop() override;
                    };

                protected:

                    std::shared_ptr<ModuleInstanceHandle> _moduleHandle;

                    elrond::interface::ConsoleAdapter* _consoleAdapter;
                    elrond::mock::Arguments* _arguments;

                    bool _loopEnable;
                    elrond::TimeSpan _loopTs;

                    static const elrond::platform::ModuleInfo mockedModuleInfo;

                    //
                    // Constructor
                    //
                    RuntimeCtx(std::shared_ptr<ModuleInstanceHandle> moduleHandle);

                public:

                    //
                    // Setters methods
                    //
                    RuntimeCtx& console(elrond::interface::ConsoleAdapter& consoleAdapter);
                    RuntimeCtx& arguments(elrond::mock::Arguments& args);

                    //
                    // Getters methods
                    //
                    elrond::Context ctx();
                    elrond::pointer<elrond::interface::Console> console() const;
                    elrond::pointer<elrond::interface::Arguments> arguments() const;
                    elrond::string name() const;
                    elrond::interface::Module& instance() const;
                    elrond::interface::Factory& factory() const;

                    bool loopEnable() const;
                    elrond::TimeSpan loopTs() const;

                    //
                    // Others methods
                    //
                    RuntimeCtx& callSetup();
                    RuntimeCtx& callStart();
                    RuntimeCtx& callLoop();
                    RuntimeCtx& callLoop(const elrond::sizeT times);
                    RuntimeCtx& callLoop(elrond::function<bool> predic);
                    RuntimeCtx& callStop();

                    //
                    // Static methods
                    //
                    template <class T>
                    static RuntimeCtx create(const elrond::string& name);

                    template <class T>
                    static RuntimeCtx create(const elrond::string& name, const elrond::platform::ModuleInfo& info);

                    static RuntimeCtx create(const elrond::string& name, const elrond::string& path);
            };
        }
    }

#endif
