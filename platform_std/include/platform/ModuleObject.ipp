#ifndef ELROND_PLATFORM_MODULE_OBJECT_IPP
    #define ELROND_PLATFORM_MODULE_OBJECT_IPP

    #include "platform/ModuleObject.hpp"
    #include "platform/RuntimeCtx.hpp"

    namespace elrond
    {
        namespace platform
        {
            ELROND_INLINE void ModuleObject::__init__(const elrond::platform::RuntimeCtx* const ctx)
            {
                if(this->___ctx___ == nullptr) this->___ctx___ = ctx;
            }

            ELROND_INLINE const elrond::interface::Context& ModuleObject::__ctx__() const
            {
                if(this->___ctx___ != nullptr) return this->___ctx___->ofInstance(*this);
                throw std::runtime_error("Invalid runtime context");
            }
        }
    }

#endif
