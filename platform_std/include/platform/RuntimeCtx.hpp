#ifndef ELROND_PLATFORM_RUNTIME_CTX_HPP
    #define ELROND_PLATFORM_RUNTIME_CTX_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            class RuntimeCtx
            {
                public:
                    virtual elrond::pointer<elrond::interface::Context>
                    ofInstance(const elrond::platform::ModuleObject& inst) const =0;
            };
        }
    }

#endif
