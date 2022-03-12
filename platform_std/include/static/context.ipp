#ifndef ELROND_PLATFORM_STATIC_CONTEXT_IPP
    #define ELROND_PLATFORM_STATIC_CONTEXT_IPP

    #include "static/context.hpp"

    /*  **********************************************************************
        *************** Elrond context functions implementation **************
        ********************************************************************** */

    namespace elrond
    {
        ELROND_INLINE elrond::pointer<elrond::interface::Context>
        ctx(const elrond::interface::Module& inst)
        { return inst.__ctx__(); }

        ELROND_INLINE elrond::pointer<elrond::interface::Context>
        ctx(const elrond::interface::Module* const inst)
        {
            if(inst != nullptr) return inst->__ctx__();
            throw std::runtime_error("Invalid module instance");
        }
    }

#endif
