#ifndef ELROND_PLATFORM_MODULE_OBJECT_HPP
    #define ELROND_PLATFORM_MODULE_OBJECT_HPP

    #include "elrond_common_types.hpp"
    
    namespace elrond
    {
        namespace platform
        {
            class ModuleObject
            {
                private:
                    const elrond::platform::RuntimeCtx* ___ctx___ = nullptr;

                public:
                    virtual ~ModuleObject() = ELROND_DEFAULT_DESTRUCTOR;

                    void __init__(const elrond::platform::RuntimeCtx * const ctx);
                    elrond::pointer<elrond::interface::Context> __ctx__() const;
            };
        }
    }

#endif
