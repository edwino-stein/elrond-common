#ifndef ELROND_MOCK_RUNTIME_CTX_HPP
    #define ELROND_MOCK_RUNTIME_CTX_HPP

    #include "mock/Application.hpp"

    namespace elrond
    {
        namespace mock
        {
            class RuntimeCtx : public elrond::mock::Application
            {
                protected:
                    std::shared_ptr<ModuleInstanceHandle> _moduleHandle;

                    //
                    // Constructor
                    //
                    RuntimeCtx(std::shared_ptr<ModuleInstanceHandle> moduleHandle);

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(RuntimeCtx, =delete, =default, =default, =default, =default)

                    elrond::pointer<elrond::interface::Context> makeCtx();

                    //
                    // Getters methods
                    //
                    ModuleInstanceHandle& moduleHandle() const;
                    elrond::interface::Module& instance() const;
                    elrond::interface::Factory& factory() const;

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

            class Context : public elrond::interface::Context
            {
                protected:
                    RuntimeCtx* _app;

                public:

                    ELROND_CLASS_SPECIAL_MEMBERS(Context, =delete, =delete, =delete, =delete, =delete)
                    Context(RuntimeCtx& app);

                    elrond::pointer<elrond::interface::Console> console() const override;
                    elrond::pointer<elrond::interface::Arguments> arguments() const override;
                    elrond::string name() const override;

                    void setLoopEvery(const elrond::TimeSpan& ts) override;
                    void unsetLoop() override;
            };
        }
    }
#endif
