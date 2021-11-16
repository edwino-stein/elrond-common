#ifndef ELROND_MOCK_RUNTIME_CTX_HPP
    #define ELROND_MOCK_RUNTIME_CTX_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class RuntimeCtx : public elrond::interface::Context,
                               public elrond::platform::RuntimeCtx
            {
                protected:

                    elrond::string name;
                    std::unique_ptr<elrond::interface::Module> inst;

                    elrond::interface::Console* consoleInst;

                    RuntimeCtx(elrond::string name, elrond::interface::Module* const inst);

                public:

                    elrond::interface::Console const& console() const override;

                    elrond::interface::Context const&
                    ofInstance(const elrond::platform::ModuleObject& inst) const override;

                    RuntimeCtx& console(elrond::interface::Console& console);

                    RuntimeCtx& callSetup();
                    RuntimeCtx& callStart();
                    RuntimeCtx& callLoop();
                    RuntimeCtx& callLoop(const elrond::sizeT times);
                    RuntimeCtx& callLoop(elrond::function<bool> predic);
                    RuntimeCtx& callStop();

                    template <class T>
                    static RuntimeCtx create(elrond::string name);
            };
        }
    }

#endif
