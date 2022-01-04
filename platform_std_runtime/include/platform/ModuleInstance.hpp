#ifndef ELROND_PLATFORM_RUNTIME_MODULE_INSTANCE_HPP
    #define ELROND_PLATFORM_RUNTIME_MODULE_INSTANCE_HPP

    #include "elrond_platform_runtime_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            class ModuleInstance
            {
                private:

                    const elrond::string _name;
                    const ModuleInstanceH _instance;

                public:

                    ModuleInstance(const elrond::string& name, const FactoryInterface& factory);
                    virtual ~ModuleInstance();

                    elrond::interface::Module& instance() const;
                    const elrond::string& name() const;
            };
        }
    }

#endif
