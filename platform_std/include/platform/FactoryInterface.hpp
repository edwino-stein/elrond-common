#ifndef ELROND_PLATFORM_FACTORY_INTERFACE_HPP
    #define ELROND_PLATFORM_FACTORY_INTERFACE_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            class FactoryInterface
            {
                public:
                    virtual ~FactoryInterface() = default;

                    virtual elrond::dWord apiVersion() const =0;
                    virtual const elrond::string& name() const =0;
                    virtual const ModuleInfo& info() const =0;

                    virtual elrond::interface::Module* create() const =0;
                    virtual void destroy(elrond::interface::Module* inst) const =0;
            };
        }
    }

#endif
