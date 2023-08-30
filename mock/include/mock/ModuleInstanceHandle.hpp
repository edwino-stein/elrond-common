#ifndef ELROND_MOCK_MODULE_INSTANCE_HANDLE_HPP
    #define ELROND_MOCK_MODULE_INSTANCE_HANDLE_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class ModuleInstanceHandle
            {
                protected:
                    elrond::string _name;
                    elrond::interface::Module* _instance;

                    ModuleInstanceHandle(const elrond::string& name);

                public:
                    bool loopEnable;
                    elrond::TimeSpan loopTs;

                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(ModuleInstanceHandle)

                    virtual elrond::interface::Factory& factory() const =0;
                    elrond::string name() const;
                    elrond::interface::Module& instance() const;
            };

            class ExternalInstanceModuleHandle : public ModuleInstanceHandle
            {
                protected:
                    elrond::platform::DlHandle _dlHandle;
                    elrond::interface::Factory& _factory;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS_CONSTUCTORS(ExternalInstanceModuleHandle, =delete, =delete, =delete, =delete, =delete)
                    ExternalInstanceModuleHandle(const elrond::string& name, const elrond::string& path);
                    virtual ~ExternalInstanceModuleHandle();

                    elrond::interface::Factory& factory() const override;
            };

            template <class T>
            class InternalInstanceModuleHandle : public ModuleInstanceHandle
            {
                private:
                    elrond::platform::Factory<T> _factory;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS_CONSTUCTORS(InternalInstanceModuleHandle, =delete, =delete, =delete, =delete, =delete)
                    InternalInstanceModuleHandle(const elrond::string& name, const elrond::platform::ModuleInfo& info);
                    virtual ~InternalInstanceModuleHandle();

                    elrond::interface::Factory& factory() const override;
            };
        }
    }

#endif
