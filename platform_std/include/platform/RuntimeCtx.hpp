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
                    virtual elrond::interface::Context const&
                    ofInstance(const elrond::platform::ModuleObject& inst) const =0;
            };
        }
    }

#endif
