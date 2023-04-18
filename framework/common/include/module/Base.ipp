#ifndef ELROND_COMMON_MODULE_BASE_IPP
    #define ELROND_COMMON_MODULE_BASE_IPP

    #include "module/Base.hpp"

    namespace elrond
    {
        namespace module
        {
            template<elrond::ModuleType M>
            elrond::ModuleType Base<M>::moduleType() const { return M; }
        }
    }

#endif
