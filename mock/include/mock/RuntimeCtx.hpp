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

                            const RuntimeCtx& ctx;

                            Context(const RuntimeCtx& ctx);

                            elrond::pointer<elrond::interface::Console>
                            console() const override;

                            elrond::pointer<elrond::interface::Arguments>
                            arguments() const override;

                            elrond::string name() const override;

                            void loopEnable(bool enable) override;
                            void loopInterval(elrond::timeT interval) override;
                            void loopAsync(bool enable) override;
                    };

                protected:

                    //
                    // Module instance Handle properties
                    //
                    elrond::platform::FactoryAdapterP _adapter;
                    elrond::platform::ModuleInstanceP _instance;

                    //
                    // Internal properties
                    //
                    elrond::interface::ConsoleAdapter* _consoleAdapter;
                    elrond::mock::Arguments* _arguments;
                    bool _loopEnable;
                    bool _loopAsync;
                    elrond::timeT _loopInterval;

                    static const elrond::platform::ModuleInfo mockedModuleInfo;

                    //
                    // Constructor
                    //
                    RuntimeCtx(elrond::string name, elrond::platform::FactoryAdapterP adapter);

                public:

                    //
                    // Setters methods
                    //
                    RuntimeCtx& console(elrond::interface::ConsoleAdapter& consoleAdapter);
                    RuntimeCtx& arguments(elrond::mock::Arguments& args);

                    //
                    // Getters methods
                    //
                    elrond::ContextP ctx() const;
                    elrond::pointer<elrond::interface::Console> console() const;
                    elrond::pointer<elrond::interface::Arguments> arguments() const;
                    elrond::string name() const;
                    elrond::interface::Module& instance() const;
                    elrond::platform::BaseFactoryAdapter& adapter() const;

                    bool loopEnable() const;
                    elrond::timeT loopInterval() const;
                    bool loopAsync() const;

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
                    static RuntimeCtx create(elrond::string name);

                    template <class T>
                    static RuntimeCtx create(elrond::string name, elrond::platform::ModuleInfo& info);

                    static RuntimeCtx create(elrond::string name, elrond::string path);
            };
        }
    }

#endif
