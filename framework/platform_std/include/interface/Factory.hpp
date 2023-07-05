#ifndef ELROND_PLATFORM_INTERFACE_FACTORY_HPP
    #define ELROND_PLATFORM_INTERFACE_FACTORY_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Factory
            {
                public:

                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(Factory)

                    virtual elrond::dWord apiVersion() const =0;
                    virtual const elrond::platform::ModuleInfo& info() const =0;

                    virtual elrond::interface::Module* create() const =0;
                    virtual void destroy(elrond::interface::Module* inst) const =0;
            };
        }
    }

#endif
